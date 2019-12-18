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
struct tui_layout_def {int split; } ;

/* Variables and functions */
 int /*<<< orphan*/  tui_enable () ; 
 int /*<<< orphan*/  tui_handle_xdb_layout (struct tui_layout_def*) ; 
 struct tui_layout_def* tui_layout_def () ; 

__attribute__((used)) static void
tui_toggle_split_layout_command (char *arg, int from_tty)
{
  struct tui_layout_def * layout_def = tui_layout_def ();

  /* Make sure the curses mode is enabled.  */
  tui_enable ();
  layout_def->split = (!layout_def->split);
  tui_handle_xdb_layout (layout_def);
}