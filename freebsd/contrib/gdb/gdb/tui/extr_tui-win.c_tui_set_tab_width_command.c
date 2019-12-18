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
 int atoi (char*) ; 
 int /*<<< orphan*/  tui_enable () ; 
 int /*<<< orphan*/  tui_set_default_tab_len (int) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
tui_set_tab_width_command (char *arg, int from_tty)
{
  /* Make sure the curses mode is enabled.  */
  tui_enable ();
  if (arg != (char *) NULL)
    {
      int ts;

      ts = atoi (arg);
      if (ts > 0)
	tui_set_default_tab_len (ts);
      else
	warning ("Tab widths greater than 0 must be specified.\n");
    }
}