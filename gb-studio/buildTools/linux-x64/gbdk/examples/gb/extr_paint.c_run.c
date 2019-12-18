#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HIDE_SPRITES ; 
 int J_A ; 
 int J_B ; 
 int J_DOWN ; 
 int J_LEFT ; 
 int J_RIGHT ; 
 int J_SELECT ; 
 int J_UP ; 
 int /*<<< orphan*/  SHOW_SPRITES ; 
 int /*<<< orphan*/  SOLID ; 
 int /*<<< orphan*/  WHITE ; 
 int /*<<< orphan*/ * colors ; 
 size_t current_color ; 
 size_t current_mode ; 
 int cursor_x ; 
 int cursor_y ; 
 int joypad () ; 
 int /*<<< orphan*/  menu () ; 
 int /*<<< orphan*/ * modes ; 
 int /*<<< orphan*/  move_cursor () ; 
 int /*<<< orphan*/  plot (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cursor () ; 
 int /*<<< orphan*/  wait_vbl_done () ; 

void run()
{
  UBYTE key;
  UBYTE slowdown;
  UBYTE drawn, erased;

  slowdown = 10;
  drawn = erased = 0;

  set_cursor();
  move_cursor();
  SHOW_SPRITES;

  while(1) {
    wait_vbl_done();
    key = joypad();
    if(key & (J_UP|J_DOWN|J_LEFT|J_RIGHT)) {
      if(key & J_UP && cursor_y > 0)
	cursor_y--;
      if(key & J_DOWN && cursor_y < 143)
	cursor_y++;
      if(key & J_LEFT && cursor_x > 0)
	cursor_x--;
      if(key & J_RIGHT && cursor_x < 159)
	cursor_x++;
      move_cursor();
      while(slowdown && key == joypad()) {
	wait_vbl_done();
	slowdown--;
      }
      slowdown = 1;
      drawn = erased = 0;
    } else
      slowdown = 10;
    if(key & J_SELECT) {
      HIDE_SPRITES;
      menu();
      set_cursor();
      move_cursor();
      SHOW_SPRITES;
    }
    if((key & (J_A|J_B)) == J_A) {
      if(!drawn) {
	drawn++;
	plot(cursor_x, cursor_y, colors[current_color], modes[current_mode]);
      }
    } else
      drawn = 0;
    if((key & (J_A|J_B)) == J_B) {
      if(!erased) {
	erased++;
	plot(cursor_x, cursor_y, WHITE, SOLID);
      }
    } else
      erased = 0;
  }
}