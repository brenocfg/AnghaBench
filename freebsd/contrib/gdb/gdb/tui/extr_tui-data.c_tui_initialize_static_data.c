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
 int /*<<< orphan*/  tui_disassem_exec_info_win_ptr () ; 
 int /*<<< orphan*/  tui_init_generic_part (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_locator_win_info_ptr () ; 
 int /*<<< orphan*/  tui_source_exec_info_win_ptr () ; 

void
tui_initialize_static_data (void)
{
  tui_init_generic_part (tui_source_exec_info_win_ptr ());
  tui_init_generic_part (tui_disassem_exec_info_win_ptr ());
  tui_init_generic_part (tui_locator_win_info_ptr ());
}