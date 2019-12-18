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
 scalar_t__ TUI_SINGLE_KEY_MODE ; 
 int /*<<< orphan*/  tui_active ; 
 scalar_t__ tui_current_key_mode ; 
 int /*<<< orphan*/  tui_rl_switch_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_key_mode (scalar_t__) ; 

__attribute__((used)) static int
tui_rl_next_keymap (int notused1, int notused2)
{
  if (!tui_active)
    tui_rl_switch_mode (0/*notused*/, 0/*notused*/);

  tui_set_key_mode (tui_current_key_mode == TUI_COMMAND_MODE
                    ? TUI_SINGLE_KEY_MODE : TUI_COMMAND_MODE);
  return 0;
}