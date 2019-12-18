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
 int /*<<< orphan*/  LAYOUT_USAGE ; 
 scalar_t__ TUI_SUCCESS ; 
 int /*<<< orphan*/  tui_enable () ; 
 scalar_t__ tui_set_layout_for_display_command (char*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tui_layout_command (char *arg, int from_tty)
{
  /* Make sure the curses mode is enabled.  */
  tui_enable ();

  /* Switch to the selected layout.  */
  if (tui_set_layout_for_display_command (arg) != TUI_SUCCESS)
    warning ("Invalid layout specified.\n%s", LAYOUT_USAGE);

}