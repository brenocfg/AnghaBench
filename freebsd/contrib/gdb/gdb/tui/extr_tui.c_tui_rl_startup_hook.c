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
 scalar_t__ TUI_COMMAND_MODE ; 
 int /*<<< orphan*/  TUI_SINGLE_KEY_MODE ; 
 int rl_already_prompted ; 
 scalar_t__ tui_current_key_mode ; 
 int /*<<< orphan*/  tui_redisplay_readline () ; 
 int /*<<< orphan*/  tui_set_key_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tui_rl_startup_hook (void)
{
  rl_already_prompted = 1;
  if (tui_current_key_mode != TUI_COMMAND_MODE)
    tui_set_key_mode (TUI_SINGLE_KEY_MODE);
  tui_redisplay_readline ();
  return 0;
}