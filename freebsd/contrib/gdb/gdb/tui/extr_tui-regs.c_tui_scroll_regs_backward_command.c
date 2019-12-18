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
 int /*<<< orphan*/  BACKWARD_SCROLL ; 
 int /*<<< orphan*/  TUI_DATA_WIN ; 
 int /*<<< orphan*/  tui_scroll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tui_scroll_regs_backward_command (char *arg, int from_tty)
{
  tui_scroll (BACKWARD_SCROLL, TUI_DATA_WIN, 1);
}