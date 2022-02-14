//Import I2C library and declare its adress
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

/*
  Initiat Code from https://www.carnetdumaker.net/articles/mesurer-une-distance-avec-un-capteur-ultrason-hc-sr04-et-une-carte-arduino-genuino/
  I displayed the values on the LCD screen and sarial monitor
*/

/* Pin constants */
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
 
/* Constants for the timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Speed of sound in air in mm/us */
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
   
  // Initialise le port série and the LCD
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}

void loop() {

  /* 1. Initiates a distance measurement by sending a HIGH pulse of 10µs on the TRIGGER pin */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  /* 2. Measures the time between the sending of the ultrasonic pulse and its echo (if it exists) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);

  /* 3. Calculate distance from measured time */
  float distance_mm = measure / 2.0 * SOUND_SPEED;

  /* Displays results in mm, cm and m */
  // In Serial monitor
  Serial.print(F("Distance: "));
  Serial.print(distance_mm);
  // Print value to LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(9, 0);
  lcd.print(distance_mm);
  Serial.print(F("mm ("));
  Serial.print(distance_mm / 10.0, 2);
  Serial.print(F("cm, "));
  Serial.print(distance_mm / 1000.0, 2);
  Serial.println(F("m)"));

  /* Timeout to avoid displaying too many results per second */   delay(2000);
  lcd.clear();
}