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
 scalar_t__ lease_state ; 
 int /*<<< orphan*/  lst_finish ; 
 scalar_t__ lst_on ; 
 int /*<<< orphan*/  run_rpc_lease () ; 

void do_rpc_stop_lease (void) {
  if (lease_state != lst_on) {
    return;
  }
  lease_change_state (lst_finish);
  run_rpc_lease();
}