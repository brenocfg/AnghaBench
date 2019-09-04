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
 scalar_t__ MAIN_REPLICA ; 
 scalar_t__ MANIFEST ; 
 int /*<<< orphan*/  check_manifest_updates () ; 
 int /*<<< orphan*/  delete_dead_connections () ; 
 int /*<<< orphan*/  request_binlog () ; 
 int /*<<< orphan*/  update_binlog_position () ; 

void cluster_precise_cron (void) {
  if (MAIN_REPLICA) {
    update_binlog_position ();
  } else {
    request_binlog ();
  }
  if (MANIFEST) {
    check_manifest_updates ();
  }
  delete_dead_connections ();
}