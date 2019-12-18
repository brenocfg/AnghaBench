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
 scalar_t__ detach_hook ; 
 scalar_t__ print_frame_info_listing_hook ; 
 scalar_t__ query_hook ; 
 scalar_t__ register_changed_hook ; 
 scalar_t__ registers_changed_hook ; 
 scalar_t__ selected_frame_level_changed_hook ; 
 int /*<<< orphan*/  set_gdb_event_hooks (int /*<<< orphan*/ ) ; 
 scalar_t__ target_wait_hook ; 
 int /*<<< orphan*/  tui_old_event_hooks ; 

void
tui_remove_hooks (void)
{
  target_wait_hook = 0;
  selected_frame_level_changed_hook = 0;
  print_frame_info_listing_hook = 0;
  query_hook = 0;
  registers_changed_hook = 0;
  register_changed_hook = 0;
  detach_hook = 0;

  /* Restore the previous event hooks.  */
  set_gdb_event_hooks (tui_old_event_hooks);
}