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
 int /*<<< orphan*/  lease_change_state (int /*<<< orphan*/ ) ; 
 scalar_t__ lease_ready_flag ; 
 scalar_t__ lease_state ; 
 int /*<<< orphan*/  lst_finish ; 
 scalar_t__ lst_on ; 
 scalar_t__ precise_now ; 
 scalar_t__ rpc_lease_timeout ; 
 int /*<<< orphan*/  run_rpc_lease () ; 

void lease_cron (void) {
  int need = 0;

  if (lease_state == lst_on && rpc_lease_timeout < precise_now) {
    lease_change_state (lst_finish);
    need = 1;
  }
  if (lease_ready_flag) {
    need = 1;
  }
  if (need) {
    run_rpc_lease();
  }
}