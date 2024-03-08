#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
// modul RTC DS3231.............
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD 16x2 dapat berbeda, disesuaikan dengan modul Anda

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
// Menampilkan Jam................
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
   Serial.println("Time :");
  lcd.print(now.hour(), DEC);
  Serial.println(now.hour(), DEC);
  lcd.print(':');

  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(':');

  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);

// menampilkan tanggal ..................
  char tanggal[20];
  sprintf(tanggal, "%d %s %d", now.day(), getBulanIndonesia(now.month()), now.year());
  Serial.println(tanggal);
  // Menampilkan Tangal
  lcd.setCursor(4, 1);
  
  lcd.print(tanggal);

  delay(1000);
}
const char *getBulanIndonesia(int bulan) {
  switch (bulan) {
    case 1: return "Januari";
    case 2: return "Februari";
    case 3: return "Maret";
    case 4: return "April";
    case 5: return "Mei";
    case 6: return "Juni";
    case 7: return "Juli";
    case 8: return "Agustus";
    case 9: return "September";
    case 10: return "Oktober";
    case 11: return "November";
    case 12: return "Desember";
    default: return "Bulan tidak valid";
  }
}