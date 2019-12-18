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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DISASSEM_WIN ; 
 int /*<<< orphan*/  tui_add_win_to_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_source_windows_with_addr (int /*<<< orphan*/ ) ; 

void
tui_show_assembly (CORE_ADDR addr)
{
  tui_add_win_to_layout (DISASSEM_WIN);
  tui_update_source_windows_with_addr (addr);
}