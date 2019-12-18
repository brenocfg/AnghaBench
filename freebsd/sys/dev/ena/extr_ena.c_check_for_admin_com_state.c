#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  admin_q_pause; } ;
struct ena_adapter {int /*<<< orphan*/  reset_reason; TYPE_1__ dev_stats; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_ADMIN_TO ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ena_com_get_admin_running_state (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void check_for_admin_com_state(struct ena_adapter *adapter)
{
	if (unlikely(ena_com_get_admin_running_state(adapter->ena_dev) ==
	    false)) {
		device_printf(adapter->pdev,
		    "ENA admin queue is not in running state!\n");
		counter_u64_add(adapter->dev_stats.admin_q_pause, 1);
		if (likely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))) {
			adapter->reset_reason = ENA_REGS_RESET_ADMIN_TO;
			ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET, adapter);
		}
	}
}