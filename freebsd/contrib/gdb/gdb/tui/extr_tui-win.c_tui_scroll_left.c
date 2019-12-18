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
struct tui_win_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEFT_SCROLL ; 
 struct tui_win_info* TUI_CMD_WIN ; 
 struct tui_win_info* TUI_DISASM_WIN ; 
 struct tui_win_info* TUI_SRC_WIN ; 
 int /*<<< orphan*/  tui_horizontal_source_scroll (struct tui_win_info*,int /*<<< orphan*/ ,int) ; 

void
tui_scroll_left (struct tui_win_info * win_to_scroll, int num_to_scroll)
{
  if (win_to_scroll != TUI_CMD_WIN)
    {
      int _num_to_scroll = num_to_scroll;

      if (_num_to_scroll == 0)
	_num_to_scroll = 1;
      /*
         ** If we are scrolling the source or disassembly window, do a
         ** "psuedo" scroll since not all of the source is in memory,
         ** only what is in the viewport. If win_to_scroll is the
         ** command window do nothing since the term should handle it.
       */
      if (win_to_scroll == TUI_SRC_WIN || win_to_scroll == TUI_DISASM_WIN)
	tui_horizontal_source_scroll (win_to_scroll, LEFT_SCROLL, _num_to_scroll);
    }
}