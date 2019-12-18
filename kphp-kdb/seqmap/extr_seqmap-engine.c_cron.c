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
 int /*<<< orphan*/  check_child_status () ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  flush_binlog () ; 
 scalar_t__ force_write_index ; 
 int /*<<< orphan*/  fork_write_index () ; 
 int /*<<< orphan*/  free_by_time () ; 
 int /*<<< orphan*/  last_reindex_on_low_memory_time ; 
 scalar_t__ memory_full_warning () ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  redistribute_memory () ; 
 int /*<<< orphan*/  reindex_on_low_memory ; 

void cron (void) {
  create_all_outbound_connections ();
  flush_binlog ();
  free_by_time ();
  redistribute_memory ();
  if (!reindex_on_low_memory && memory_full_warning ()) {
    force_write_index ++;
    reindex_on_low_memory ++;
    last_reindex_on_low_memory_time = now;
  }
  if (force_write_index) {
    fork_write_index ();
  }
  check_child_status();
}