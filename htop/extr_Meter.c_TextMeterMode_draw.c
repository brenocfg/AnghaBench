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
 int METER_BUFFER_LEN ; 
 size_t METER_TEXT ; 
 int /*<<< orphan*/  Meter_displayBuffer (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Meter_updateValues (TYPE_1__*,char*,int) ; 
 size_t RESET_COLOR ; 
 int /*<<< orphan*/  RichString_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RichString_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RichString_printVal (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  attrset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvaddstr (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TextMeterMode_draw(Meter* this, int x, int y, int w) {
   char buffer[METER_BUFFER_LEN];
   Meter_updateValues(this, buffer, METER_BUFFER_LEN - 1);
   (void) w;

   attrset(CRT_colors[METER_TEXT]);
   mvaddstr(y, x, this->caption);
   int captionLen = strlen(this->caption);
   x += captionLen;
   attrset(CRT_colors[RESET_COLOR]);
   RichString_begin(out);
   Meter_displayBuffer(this, buffer, &out);
   RichString_printVal(out, y, x);
   RichString_end(out);
}