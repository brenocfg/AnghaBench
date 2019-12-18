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
 int /*<<< orphan*/  lst_finish ; 
 int /*<<< orphan*/  lst_on ; 
 scalar_t__ lst_start ; 
 scalar_t__ rpc_stopped ; 

int lease_start (void) {
  assert (lease_state == lst_start);
  if (has_pending_scripts()) {
    return 0;
  }
  lease_change_state (lst_on);
  lease_ready_flag = 1;
  if (rpc_stopped) {
    lease_change_state (lst_finish);
  }
  return 1;
}