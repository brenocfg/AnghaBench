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
 int /*<<< orphan*/  endwin () ; 
 scalar_t__ rl_already_prompted ; 
 int /*<<< orphan*/  rl_set_keymap (int /*<<< orphan*/ ) ; 
 scalar_t__ rl_startup_hook ; 
 int /*<<< orphan*/  target_terminal_save_ours () ; 
 scalar_t__ tui_active ; 
 int /*<<< orphan*/  tui_readline_standard_keymap ; 
 int /*<<< orphan*/  tui_remove_hooks () ; 
 int /*<<< orphan*/  tui_setup_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_gdb_sizes () ; 

void
tui_disable (void)
{
  if (!tui_active)
    return;

  /* Restore initial readline keymap.  */
  rl_set_keymap (tui_readline_standard_keymap);

  /* Remove TUI hooks.  */
  tui_remove_hooks ();
  rl_startup_hook = 0;
  rl_already_prompted = 0;

  /* Leave curses and restore previous gdb terminal setting.  */
  endwin ();

  /* gdb terminal has changed, update gdb internal copy of it
     so that terminal management with the inferior works.  */
  tui_setup_io (0);

  /* Update gdb's knowledge of its terminal.  */
  target_terminal_save_ours ();

  tui_active = 0;
  tui_update_gdb_sizes ();
}