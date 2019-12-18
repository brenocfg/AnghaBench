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
 int /*<<< orphan*/  TUI_ONE_COMMAND_MODE ; 
 int rl_insert (int,int) ; 
 int /*<<< orphan*/  tui_set_key_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tui_rl_command_mode (int count, int key)
{
  tui_set_key_mode (TUI_ONE_COMMAND_MODE);
  return rl_insert (count, key);
}