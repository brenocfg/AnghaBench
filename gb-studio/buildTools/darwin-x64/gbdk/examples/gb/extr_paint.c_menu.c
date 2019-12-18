#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBYTE ;
struct TYPE_2__ {size_t up; size_t down; size_t left; size_t right; scalar_t__ cursor; } ;

/* Variables and functions */
 scalar_t__ ARROW ; 
 scalar_t__ FIRST_COLOR ; 
 scalar_t__ FIRST_MODE ; 
 scalar_t__ FIRST_TOOL ; 
 int /*<<< orphan*/  HIDE_SPRITES ; 
 scalar_t__ J_A ; 
 scalar_t__ J_DOWN ; 
 scalar_t__ J_LEFT ; 
 scalar_t__ J_RIGHT ; 
 scalar_t__ J_SELECT ; 
 scalar_t__ J_UP ; 
 size_t LAST_COLOR ; 
 size_t LAST_MODE ; 
 size_t LAST_TOOL ; 
 scalar_t__ NB_TOOLS ; 
 int /*<<< orphan*/  SELECTED ; 
 int /*<<< orphan*/  SHOW_SPRITES ; 
 int /*<<< orphan*/  UNSELECTED ; 
 int /*<<< orphan*/  change_icon (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ current_color ; 
 scalar_t__ current_cursor ; 
 scalar_t__ current_mode ; 
 size_t current_tool ; 
 TYPE_1__* icons ; 
 scalar_t__ joypad () ; 
 size_t menu_cursor_pos ; 
 int /*<<< orphan*/  move_menu_cursor () ; 
 int /*<<< orphan*/  reset_icon (scalar_t__) ; 
 int /*<<< orphan*/  set_cursor () ; 
 int /*<<< orphan*/  set_icon (scalar_t__,int) ; 
 int /*<<< orphan*/  wait_vbl_done () ; 
 int /*<<< orphan*/  waitpadup () ; 

void menu()
{
  UBYTE i, key;
  UBYTE slowdown;
  UBYTE cursor;

  slowdown = 50;

  for(i = 0; i < NB_TOOLS; i++)
    set_icon(i,
	     i == FIRST_TOOL + current_tool ||
	     i == FIRST_COLOR + current_color ||
	     i == FIRST_MODE + current_mode);

  cursor = current_cursor;
  current_cursor = ARROW;
  set_cursor();
  move_menu_cursor();
  SHOW_SPRITES;
  waitpadup();
  do {
    wait_vbl_done();
    key = joypad();
    if(key & (J_UP|J_DOWN|J_LEFT|J_RIGHT)) {
      if(key & J_UP)
	menu_cursor_pos = icons[menu_cursor_pos].up;
      if(key & J_DOWN)
	menu_cursor_pos = icons[menu_cursor_pos].down;
      if(key & J_LEFT)
	menu_cursor_pos = icons[menu_cursor_pos].left;
      if(key & J_RIGHT)
	menu_cursor_pos = icons[menu_cursor_pos].right;
      move_menu_cursor();
      while(slowdown && key == joypad()) {
	wait_vbl_done();
	slowdown--;
      }
      slowdown = 10;
    } else
      slowdown = 50;
    if(key & J_A) {
      if( /* menu_cursor_pos >= FIRST_TOOL && */ menu_cursor_pos <= LAST_TOOL) {
	if(menu_cursor_pos != /* FIRST_TOOL + */ current_tool) {
	  change_icon(/* FIRST_TOOL + */ current_tool, UNSELECTED);
	  current_tool = menu_cursor_pos /* - FIRST_TOOL */;
	  change_icon(/* FIRST_TOOL + */ current_tool, SELECTED);
	  cursor = icons[/* FIRST_TOOL + */ current_tool].cursor;
	}
      } else if(menu_cursor_pos >= FIRST_COLOR && menu_cursor_pos <= LAST_COLOR) {
	if(menu_cursor_pos != FIRST_COLOR + current_color) {
	  change_icon(FIRST_COLOR + current_color, UNSELECTED);
	  current_color = menu_cursor_pos - FIRST_COLOR;
	  change_icon(FIRST_COLOR + current_color, SELECTED);
	}
      } else if(menu_cursor_pos >= FIRST_MODE && menu_cursor_pos <= LAST_MODE) {
	if(menu_cursor_pos != FIRST_MODE + current_mode) {
	  change_icon(FIRST_MODE + current_mode, UNSELECTED);
	  current_mode = menu_cursor_pos - FIRST_MODE;
	  change_icon(FIRST_MODE + current_mode, SELECTED);
	}
      }
    }
  } while(key != J_SELECT);
  waitpadup();
  for(i = 0; i < NB_TOOLS; i++)
    reset_icon(i);
  HIDE_SPRITES;
  current_cursor = cursor;
}