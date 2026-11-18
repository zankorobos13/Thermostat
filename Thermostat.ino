#include <Adafruit_MAX31865.h>

// Используем D2 (GPIO4) для CS — он не конфликтует с кнопкой прошивки
Adafruit_MAX31865 thermo = Adafruit_MAX31865(4);

#define RREF      430.0   // Опорный резистор на модуле (430 Ом для PT100)
#define RNOMINAL  100.0   // Номинал PT100 при 0°C

void setup() {
  Serial.begin(74880);
  
  // Попробуйте добавить задержку перед инициализацией
  delay(100); 
  thermo.begin(MAX31865_2WIRE);
  // Некоторые клоны требуют явного включения Bias и паузы
  thermo.enableBias(true);
  delay(10);
}

void loop() {
  thermo.clearFault();
  float temp = thermo.temperature(RNOMINAL, RREF);
  Serial.print("Температура: "); 
  Serial.println(temp);
  
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Ошибка 0x"); Serial.println(fault, HEX);
    thermo.clearFault();
  }
  delay(1000);
}