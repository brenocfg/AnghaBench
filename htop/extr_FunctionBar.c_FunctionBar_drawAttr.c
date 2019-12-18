#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; char** keys; char** functions; } ;
typedef  TYPE_1__ FunctionBar ;

/* Variables and functions */
 int /*<<< orphan*/  COLS ; 
 int* CRT_colors ; 
 scalar_t__ CRT_cursorX ; 
 size_t FUNCTION_BAR ; 
 size_t FUNCTION_KEY ; 
 scalar_t__ LINES ; 
 size_t RESET_COLOR ; 
 int /*<<< orphan*/  attrset (int) ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int /*<<< orphan*/  mvaddstr (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  mvhline (scalar_t__,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void FunctionBar_drawAttr(const FunctionBar* this, char* buffer, int attr) {
   attrset(CRT_colors[FUNCTION_BAR]);
   mvhline(LINES-1, 0, ' ', COLS);
   int x = 0;
   for (int i = 0; i < this->size; i++) {
      attrset(CRT_colors[FUNCTION_KEY]);
      mvaddstr(LINES-1, x, this->keys[i]);
      x += strlen(this->keys[i]);
      attrset(CRT_colors[FUNCTION_BAR]);
      mvaddstr(LINES-1, x, this->functions[i]);
      x += strlen(this->functions[i]);
   }
   if (buffer) {
      attrset(attr);
      mvaddstr(LINES-1, x, buffer);
      CRT_cursorX = x + strlen(buffer);
      curs_set(1);
   } else {
      curs_set(0);
   }
   attrset(CRT_colors[RESET_COLOR]);
}