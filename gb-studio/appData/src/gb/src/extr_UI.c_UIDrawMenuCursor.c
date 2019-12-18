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
 int menu_index ; 
 int menu_num_options ; 
 int /*<<< orphan*/  set_win_tiles (int,int,int,int,int /*<<< orphan*/ ) ; 
 int text_num_lines ; 
 int /*<<< orphan*/  ui_bg_tiles ; 
 int /*<<< orphan*/  ui_cursor_tiles ; 

void UIDrawMenuCursor() 
{
  UBYTE i;
  for (i = 0; i < menu_num_options; i++) 
  {
    set_win_tiles(i >= text_num_lines ? 10 : 1, (i % text_num_lines) + 1, 1, 1, menu_index == i ? ui_cursor_tiles : ui_bg_tiles);
  }
}