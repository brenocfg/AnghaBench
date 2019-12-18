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
struct TYPE_2__ {int /*<<< orphan*/  interface_down; } ;
struct ena_adapter {TYPE_1__ dev_stats; int /*<<< orphan*/  pdev; int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  ena_dev; int /*<<< orphan*/  ifp; int /*<<< orphan*/  timer_service; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_CLEAR_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ena_com_dev_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_destroy_all_io_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_rx_bufs (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_rx_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_tx_bufs (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_tx_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_io_irq (struct ena_adapter*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void
ena_down(struct ena_adapter *adapter)
{
	int rc;

	if (ENA_FLAG_ISSET(ENA_FLAG_DEV_UP, adapter)) {
		device_printf(adapter->pdev, "device is going DOWN\n");

		callout_drain(&adapter->timer_service);

		ENA_FLAG_CLEAR_ATOMIC(ENA_FLAG_DEV_UP, adapter);
		if_setdrvflagbits(adapter->ifp, IFF_DRV_OACTIVE,
		    IFF_DRV_RUNNING);

		ena_free_io_irq(adapter);

		if (ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter)) {
			rc = ena_com_dev_reset(adapter->ena_dev,
			    adapter->reset_reason);
			if (unlikely(rc != 0))
				device_printf(adapter->pdev,
				    "Device reset failed\n");
		}

		ena_destroy_all_io_queues(adapter);

		ena_free_all_tx_bufs(adapter);
		ena_free_all_rx_bufs(adapter);
		ena_free_all_tx_resources(adapter);
		ena_free_all_rx_resources(adapter);

		counter_u64_add(adapter->dev_stats.interface_down, 1);
	}
}