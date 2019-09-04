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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ has_pending_scripts () ; 
 int /*<<< orphan*/  lease_change_state (int /*<<< orphan*/ ) ; 
 int lease_ready_flag ; 
 scalar_t__ lease_state ; 
 scalar_t__ lst_finish ; 
 int /*<<< orphan*/  lst_off ; 
 int /*<<< orphan*/  rpc_lease_target ; 
 int /*<<< orphan*/  rpc_main_target ; 
 int /*<<< orphan*/  rpct_lease_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpct_stop_ready (int /*<<< orphan*/ ) ; 

int lease_finish (void) {
  assert (lease_state == lst_finish);
  if (has_pending_scripts()) {
    return 0;
  }
  rpct_stop_ready (rpc_lease_target);
  rpct_lease_stats (rpc_main_target);
  lease_change_state (lst_off);
  lease_ready_flag = 1;
  return 1;
}