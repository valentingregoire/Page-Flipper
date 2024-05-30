/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

// #define PIN_BTN_NP 32
#define PIN_BTN_PP 16
#define PIN_BTN_PS 17
#define PIN_BTN_NP 18
#define PIN_BTN_NS 19
#define PIN_LED 21

BleKeyboard bleKeyboard("Page Flipper", "Valentin Grégoire", 100);

int btn_np = LOW;
int btn_ns = LOW;
int btn_pp = LOW;
int btn_ps = LOW;
bool btn_pressed = false;

void ping(int millis = 200) {
  digitalWrite(PIN_LED, HIGH);
  delay(millis);
  digitalWrite(PIN_LED, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  pinMode(PIN_BTN_NP, INPUT_PULLUP);
  pinMode(PIN_BTN_NS, INPUT_PULLUP);
  pinMode(PIN_BTN_PP, INPUT_PULLUP);
  pinMode(PIN_BTN_PS, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    btn_np = digitalRead(PIN_BTN_NP);
    btn_ns = digitalRead(PIN_BTN_NS);
    btn_pp = digitalRead(PIN_BTN_PP);
    btn_ps = digitalRead(PIN_BTN_PS);

    if (btn_np == LOW && !btn_pressed) {
      Serial.println("Next Page");
      btn_pressed = true;
      bleKeyboard.write('l');
      ping();
    }
    else if (btn_ns == LOW && !btn_pressed) {
      Serial.println("Previous Page");
      btn_pressed = true;
      bleKeyboard.write('h');
      ping();
    }
    else if (btn_pp == LOW && !btn_pressed) {
      Serial.println("Next Song");
      btn_pressed = true;
      bleKeyboard.write('k');
      ping();
    }
    else if (btn_ps == LOW && !btn_pressed) {
      Serial.println("Previous Song");
      btn_pressed = true;
      bleKeyboard.write('j');
      ping();
    } else {
      btn_pressed = false;
    }
  } else {
    Serial.println("Waiting for connection...");
    ping(100);
  }
}
