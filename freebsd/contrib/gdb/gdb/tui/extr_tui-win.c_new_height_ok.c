#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int height; scalar_t__ type; } ;
struct tui_win_info {TYPE_1__ generic; } ;
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;
struct TYPE_4__ {scalar_t__* list; } ;

/* Variables and functions */
 scalar_t__ CMD_WIN ; 
 int DISASSEM_COMMAND ; 
 int MIN_CMD_WIN_HEIGHT ; 
 int MIN_WIN_HEIGHT ; 
 int SRC_COMMAND ; 
 int SRC_DISASSEM_COMMAND ; 
 struct tui_win_info* TUI_CMD_WIN ; 
 struct tui_win_info* TUI_DATA_WIN ; 
 struct tui_win_info* TUI_DISASM_WIN ; 
 struct tui_win_info* TUI_SRC_WIN ; 
 int tui_current_layout () ; 
 TYPE_2__* tui_source_windows () ; 
 int tui_term_height () ; 

__attribute__((used)) static int
new_height_ok (struct tui_win_info * primary_win_info, int new_height)
{
  int ok = (new_height < tui_term_height ());

  if (ok)
    {
      int diff;
      enum tui_layout_type cur_layout = tui_current_layout ();

      diff = (new_height - primary_win_info->generic.height) * (-1);
      if (cur_layout == SRC_COMMAND || cur_layout == DISASSEM_COMMAND)
	{
	  ok = ((primary_win_info->generic.type == CMD_WIN &&
		 new_height <= (tui_term_height () - 4) &&
		 new_height >= MIN_CMD_WIN_HEIGHT) ||
		(primary_win_info->generic.type != CMD_WIN &&
		 new_height <= (tui_term_height () - 2) &&
		 new_height >= MIN_WIN_HEIGHT));
	  if (ok)
	    {			/* check the total height */
	      struct tui_win_info * win_info;

	      if (primary_win_info == TUI_CMD_WIN)
		win_info = (struct tui_win_info *) (tui_source_windows ())->list[0];
	      else
		win_info = TUI_CMD_WIN;
	      ok = ((new_height +
		     (win_info->generic.height + diff)) <= tui_term_height ());
	    }
	}
      else
	{
	  int cur_total_height, total_height, min_height = 0;
	  struct tui_win_info *first_win;
	  struct tui_win_info *second_win;

	  if (cur_layout == SRC_DISASSEM_COMMAND)
	    {
	      first_win = TUI_SRC_WIN;
	      second_win = TUI_DISASM_WIN;
	    }
	  else
	    {
	      first_win = TUI_DATA_WIN;
	      second_win = (struct tui_win_info *) (tui_source_windows ())->list[0];
	    }
	  /*
	     ** We could simply add all the heights to obtain the same result
	     ** but below is more explicit since we subtract 1 for the
	     ** line that the first and second windows share, and add one
	     ** for the locator.
	   */
	  total_height = cur_total_height =
	    (first_win->generic.height + second_win->generic.height - 1)
	    + TUI_CMD_WIN->generic.height + 1 /*locator */ ;
	  if (primary_win_info == TUI_CMD_WIN)
	    {
	      /* locator included since first & second win share a line */
	      ok = ((first_win->generic.height +
		     second_win->generic.height + diff) >=
		    (MIN_WIN_HEIGHT * 2) &&
		    new_height >= MIN_CMD_WIN_HEIGHT);
	      if (ok)
		{
		  total_height = new_height + (first_win->generic.height +
					  second_win->generic.height + diff);
		  min_height = MIN_CMD_WIN_HEIGHT;
		}
	    }
	  else
	    {
	      min_height = MIN_WIN_HEIGHT;
	      /*
	         ** First see if we can increase/decrease the command
	         ** window.  And make sure that the command window is
	         ** at least 1 line
	       */
	      ok = ((TUI_CMD_WIN->generic.height + diff) > 0);
	      if (!ok)
		{		/*
				   ** Looks like we have to increase/decrease one of
				   ** the other windows
				 */
		  if (primary_win_info == first_win)
		    ok = (second_win->generic.height + diff) >= min_height;
		  else
		    ok = (first_win->generic.height + diff) >= min_height;
		}
	      if (ok)
		{
		  if (primary_win_info == first_win)
		    total_height = new_height +
		      second_win->generic.height +
		      TUI_CMD_WIN->generic.height + diff;
		  else
		    total_height = new_height +
		      first_win->generic.height +
		      TUI_CMD_WIN->generic.height + diff;
		}
	    }
	  /*
	     ** Now make sure that the proposed total height doesn't exceed
	     ** the old total height.
	   */
	  if (ok)
	    ok = (new_height >= min_height && total_height <= cur_total_height);
	}
    }

  return ok;
}