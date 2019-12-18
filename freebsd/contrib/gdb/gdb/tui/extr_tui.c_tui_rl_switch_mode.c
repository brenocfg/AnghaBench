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
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  rl_deprep_terminal () ; 
 scalar_t__ rl_end ; 
 int /*<<< orphan*/  rl_kill_text (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rl_newline (int,char) ; 
 int /*<<< orphan*/  rl_prep_terminal (int /*<<< orphan*/ ) ; 
 scalar_t__ tui_active ; 
 int /*<<< orphan*/  tui_disable () ; 
 int /*<<< orphan*/  tui_enable () ; 

__attribute__((used)) static int
tui_rl_switch_mode (int notused1, int notused2)
{
  if (tui_active)
    {
      tui_disable ();
      rl_prep_terminal (0);
    }
  else
    {
      rl_deprep_terminal ();
      tui_enable ();
    }

  /* Clear the readline in case switching occurred in middle of something.  */
  if (rl_end)
    rl_kill_text (0, rl_end);

  /* Since we left the curses mode, the terminal mode is restored to
     some previous state.  That state may not be suitable for readline
     to work correctly (it may be restored in line mode).  We force an
     exit of the current readline so that readline is re-entered and it
     will be able to setup the terminal for its needs.  By re-entering
     in readline, we also redisplay its prompt in the non-curses mode.  */
  rl_newline (1, '\n');

  /* Make sure the \n we are returning does not repeat the last command.  */
  dont_repeat ();
  return 0;
}