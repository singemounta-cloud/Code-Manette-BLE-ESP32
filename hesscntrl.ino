  #include <BleGamepad.h>
BleGamepad controller("HessContrl", "Custom-Tech", 100);
//joystick gauche
  const int potPinX = 32;
  const int potPinY = 33;
//joystick droit
  const int potPinX1 = 34;
  const int potPinY1 = 35;
//bouton click p
  const int buttonA = 13;
  const int buttonB = 12;
  const int buttonX = 14;
  const int buttonY = 27;
//button de stick
  const int buttonL1 = 26;
  const int buttonR1 = 25;


void setup() {
  Serial.begin(115200);

//button p
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonX, INPUT_PULLUP);
  pinMode(buttonY, INPUT_PULLUP);
//button stick
  pinMode(buttonL1, INPUT_PULLUP);
  pinMode(buttonR1, INPUT_PULLUP);

  controller.begin();
  Serial.println("En attente de connexion Bluetooth.....");

}

void loop() {
  if (controller.isConnected()) {

  //actualisation des valeurs analogiques, de x et y
    int newX = analogRead(potPinX);
    int newY = analogRead(potPinY);
  //stick droit
    int newX1 = analogRead(potPinX1);
    int newY1 = analogRead(potPinY1);
  
  //conversion pour manette et on fonction de notre voltage (3.3v)
    int X = map(newX, 0, 4095, -32767, 32767);
    int Y = map(newY, 0, 4095, 32767, -32767);
  //la mm pour le stick droit
    int X1 = map(newX1, 0, 4095, -32767, 32767);
    int Y1 = map(newY1, 0, 4095, 32767, -32767);

  //on envoie la valeur analogique a notre client
    controller.setLeftThumb(X, Y);
    controller.setRightThumb(X1, Y1);

  //gestion des boutton onclick
    if (!digitalRead(buttonA)) controller.press(BUTTON_1); else controller.release(BUTTON_1);
    if (!digitalRead(buttonB)) controller.press(BUTTON_2); else controller.release(BUTTON_2);
    if (!digitalRead(buttonY)) controller.press(BUTTON_3); else controller.release(BUTTON_3);
    if (!digitalRead(buttonX)) controller.press(BUTTON_4); else controller.release(BUTTON_4);
  //gestion des click stick
    if (!digitalRead(buttonL1)) controller.press(BUTTON_5); else controller.release(BUTTON_5);
    if (!digitalRead(buttonR1)) controller.press(BUTTON_6); else controller.release(BUTTON_6);

  controller.sendReport();
  }
delay(10);
}
