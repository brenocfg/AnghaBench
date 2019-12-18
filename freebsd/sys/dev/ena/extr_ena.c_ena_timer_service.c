#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ena_admin_host_info {int dummy; } ;
struct ena_adapter {int /*<<< orphan*/  timer_service; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  reset_tq; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ifp; TYPE_2__* ena_dev; } ;
struct TYPE_3__ {struct ena_admin_host_info* host_info; } ;
struct TYPE_4__ {TYPE_1__ host_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  SBT_1S ; 
 int /*<<< orphan*/  callout_schedule_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_admin_com_state (struct ena_adapter*) ; 
 int /*<<< orphan*/  check_for_empty_rx_ring (struct ena_adapter*) ; 
 int /*<<< orphan*/  check_for_missing_completions (struct ena_adapter*) ; 
 int /*<<< orphan*/  check_for_missing_keep_alive (struct ena_adapter*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ena_update_host_info (struct ena_admin_host_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_timer_service(void *data)
{
	struct ena_adapter *adapter = (struct ena_adapter *)data;
	struct ena_admin_host_info *host_info =
	    adapter->ena_dev->host_attr.host_info;

	check_for_missing_keep_alive(adapter);

	check_for_admin_com_state(adapter);

	check_for_missing_completions(adapter);

	check_for_empty_rx_ring(adapter);

	if (host_info != NULL)
		ena_update_host_info(host_info, adapter->ifp);

	if (unlikely(ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))) {
		device_printf(adapter->pdev, "Trigger reset is on\n");
		taskqueue_enqueue(adapter->reset_tq, &adapter->reset_task);
		return;
	}

	/*
	 * Schedule another timeout one second from now.
	 */
	callout_schedule_sbt(&adapter->timer_service, SBT_1S, SBT_1S, 0);
}