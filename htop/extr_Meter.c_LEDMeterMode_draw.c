#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  caption; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 scalar_t__ CRT_utf8 ; 
 int /*<<< orphan*/  LEDMeterMode_digits ; 
 int /*<<< orphan*/  LEDMeterMode_digitsAscii ; 
 int /*<<< orphan*/  LEDMeterMode_digitsUtf8 ; 
 int /*<<< orphan*/  LEDMeterMode_drawDigit (int,int,char) ; 
 size_t LED_COLOR ; 
 int METER_BUFFER_LEN ; 
 int /*<<< orphan*/  Meter_displayBuffer (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Meter_updateValues (TYPE_1__*,char*,int) ; 
 size_t RESET_COLOR ; 
 int /*<<< orphan*/  RichString_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RichString_end (int /*<<< orphan*/ ) ; 
 char RichString_getCharVal (int /*<<< orphan*/ ,int) ; 
 int RichString_sizeVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvaddch (int,int,char) ; 
 int /*<<< orphan*/  mvaddstr (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LEDMeterMode_draw(Meter* this, int x, int y, int w) {
   (void) w;

#ifdef HAVE_LIBNCURSESW
   if (CRT_utf8)
      LEDMeterMode_digits = LEDMeterMode_digitsUtf8;
   else
#endif
      LEDMeterMode_digits = LEDMeterMode_digitsAscii;

   char buffer[METER_BUFFER_LEN];
   Meter_updateValues(this, buffer, METER_BUFFER_LEN - 1);
   
   RichString_begin(out);
   Meter_displayBuffer(this, buffer, &out);

   int yText =
#ifdef HAVE_LIBNCURSESW
      CRT_utf8 ? y+1 :
#endif
      y+2;
   attrset(CRT_colors[LED_COLOR]);
   mvaddstr(yText, x, this->caption);
   int xx = x + strlen(this->caption);
   int len = RichString_sizeVal(out);
   for (int i = 0; i < len; i++) {
      char c = RichString_getCharVal(out, i);
      if (c >= '0' && c <= '9') {
         LEDMeterMode_drawDigit(xx, y, c-48);
         xx += 4;
      } else {
         mvaddch(yText, xx, c);
         xx += 1;
      }
   }
   attrset(CRT_colors[RESET_COLOR]);
   RichString_end(out);
}