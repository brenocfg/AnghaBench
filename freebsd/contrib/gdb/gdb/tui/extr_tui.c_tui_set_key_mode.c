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
typedef  enum tui_key_mode { ____Placeholder_tui_key_mode } tui_key_mode ;

/* Variables and functions */
 int TUI_SINGLE_KEY_MODE ; 
 int /*<<< orphan*/  rl_set_keymap (int /*<<< orphan*/ ) ; 
 int tui_current_key_mode ; 
 int /*<<< orphan*/  tui_keymap ; 
 int /*<<< orphan*/  tui_readline_standard_keymap ; 
 int /*<<< orphan*/  tui_show_locator_content () ; 

void
tui_set_key_mode (enum tui_key_mode mode)
{
  tui_current_key_mode = mode;
  rl_set_keymap (mode == TUI_SINGLE_KEY_MODE
                 ? tui_keymap : tui_readline_standard_keymap);
  tui_show_locator_content ();
}