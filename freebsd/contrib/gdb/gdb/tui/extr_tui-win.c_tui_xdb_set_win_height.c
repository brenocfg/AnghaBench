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

/* Variables and functions */
 size_t CMD_WIN ; 
 scalar_t__ TUI_FAILURE ; 
 int /*<<< orphan*/  XDBWIN_HEIGHT_USAGE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  new_height_ok (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tui_adjust_win_heights (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tui_enable () ; 
 int tui_term_height () ; 
 int /*<<< orphan*/ * tui_win_list ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tui_xdb_set_win_height (char *arg, int from_tty)
{
  /* Make sure the curses mode is enabled.  */
  tui_enable ();
  if (arg != (char *) NULL)
    {
      int input_no = atoi (arg);

      if (input_no > 0)
	{			/* Add 1 for the locator */
	  int new_height = tui_term_height () - (input_no + 1);

	  if (!new_height_ok (tui_win_list[CMD_WIN], new_height) ||
	      tui_adjust_win_heights (tui_win_list[CMD_WIN],
				    new_height) == TUI_FAILURE)
	    warning ("Invalid window height specified.\n%s",
		     XDBWIN_HEIGHT_USAGE);
	}
      else
	warning ("Invalid window height specified.\n%s",
		 XDBWIN_HEIGHT_USAGE);
    }
  else
    warning ("Invalid window height specified.\n%s", XDBWIN_HEIGHT_USAGE);
}