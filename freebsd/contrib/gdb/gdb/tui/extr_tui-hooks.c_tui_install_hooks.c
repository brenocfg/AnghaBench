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
 int /*<<< orphan*/  detach_hook ; 
 int /*<<< orphan*/  print_frame_info_listing_hook ; 
 int /*<<< orphan*/  query_hook ; 
 int /*<<< orphan*/  register_changed_hook ; 
 int /*<<< orphan*/  registers_changed_hook ; 
 int /*<<< orphan*/  selected_frame_level_changed_hook ; 
 int /*<<< orphan*/  set_gdb_event_hooks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_wait_hook ; 
 int /*<<< orphan*/  tui_detach_hook ; 
 int /*<<< orphan*/  tui_event_hooks ; 
 int /*<<< orphan*/  tui_old_event_hooks ; 
 int /*<<< orphan*/  tui_print_frame_info_listing_hook ; 
 int /*<<< orphan*/  tui_query_hook ; 
 int /*<<< orphan*/  tui_register_changed_hook ; 
 int /*<<< orphan*/  tui_registers_changed_hook ; 
 int /*<<< orphan*/  tui_selected_frame_level_changed_hook ; 
 int /*<<< orphan*/  tui_target_wait_hook ; 

void
tui_install_hooks (void)
{
  target_wait_hook = tui_target_wait_hook;
  selected_frame_level_changed_hook = tui_selected_frame_level_changed_hook;
  print_frame_info_listing_hook = tui_print_frame_info_listing_hook;

  query_hook = tui_query_hook;

  /* Install the event hooks.  */
  tui_old_event_hooks = set_gdb_event_hooks (&tui_event_hooks);

  registers_changed_hook = tui_registers_changed_hook;
  register_changed_hook = tui_register_changed_hook;
  detach_hook = tui_detach_hook;
}