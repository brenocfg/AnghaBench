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
 int /*<<< orphan*/  dyn_garbage_collector () ; 
 scalar_t__ force_write_index ; 
 int /*<<< orphan*/  fork_write_index () ; 
 int /*<<< orphan*/  fsync_step () ; 
 int /*<<< orphan*/  storage_volumes_relax_astat () ; 

void cron (void) {
  storage_volumes_relax_astat ();
  create_all_outbound_connections ();
  fsync_step ();

  if (force_write_index) {
    fork_write_index ();
  }
  check_child_status ();
  dyn_garbage_collector ();
}