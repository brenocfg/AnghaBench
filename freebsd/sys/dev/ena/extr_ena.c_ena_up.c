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
struct TYPE_2__ {int /*<<< orphan*/  interface_up; } ;
struct ena_adapter {int /*<<< orphan*/  timer_service; int /*<<< orphan*/  ifp; TYPE_1__ dev_stats; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ALERT ; 
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_LINK_UP ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  SBT_1S ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ena_create_io_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_destroy_all_io_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_rx_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_tx_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_io_irq (struct ena_adapter*) ; 
 int ena_request_io_irq (struct ena_adapter*) ; 
 int ena_setup_all_rx_resources (struct ena_adapter*) ; 
 int ena_setup_all_tx_resources (struct ena_adapter*) ; 
 int ena_setup_io_intr (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_timer_service ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ena_unmask_all_io_irqs (struct ena_adapter*) ; 
 int ena_up_complete (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_update_hwassist (struct ena_adapter*) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int
ena_up(struct ena_adapter *adapter)
{
	int rc = 0;

	if (unlikely(device_is_attached(adapter->pdev) == 0)) {
		device_printf(adapter->pdev, "device is not attached!\n");
		return (ENXIO);
	}

	if (!ENA_FLAG_ISSET(ENA_FLAG_DEV_UP, adapter)) {
		device_printf(adapter->pdev, "device is going UP\n");

		/* setup interrupts for IO queues */
		rc = ena_setup_io_intr(adapter);
		if (unlikely(rc != 0)) {
			ena_trace(ENA_ALERT, "error setting up IO interrupt\n");
			goto error;
		}
		rc = ena_request_io_irq(adapter);
		if (unlikely(rc != 0)) {
			ena_trace(ENA_ALERT, "err_req_irq\n");
			goto error;
		}

		/* allocate transmit descriptors */
		rc = ena_setup_all_tx_resources(adapter);
		if (unlikely(rc != 0)) {
			ena_trace(ENA_ALERT, "err_setup_tx\n");
			goto err_setup_tx;
		}

		/* allocate receive descriptors */
		rc = ena_setup_all_rx_resources(adapter);
		if (unlikely(rc != 0)) {
			ena_trace(ENA_ALERT, "err_setup_rx\n");
			goto err_setup_rx;
		}

		/* create IO queues for Rx & Tx */
		rc = ena_create_io_queues(adapter);
		if (unlikely(rc != 0)) {
			ena_trace(ENA_ALERT,
			    "create IO queues failed\n");
			goto err_io_que;
		}

		if (ENA_FLAG_ISSET(ENA_FLAG_LINK_UP, adapter))
			if_link_state_change(adapter->ifp, LINK_STATE_UP);

		rc = ena_up_complete(adapter);
		if (unlikely(rc != 0))
			goto err_up_complete;

		counter_u64_add(adapter->dev_stats.interface_up, 1);

		ena_update_hwassist(adapter);

		if_setdrvflagbits(adapter->ifp, IFF_DRV_RUNNING,
		    IFF_DRV_OACTIVE);

		/* Activate timer service only if the device is running.
		 * If this flag is not set, it means that the driver is being
		 * reset and timer service will be activated afterwards.
		 */
		if (ENA_FLAG_ISSET(ENA_FLAG_DEVICE_RUNNING, adapter)) {
			callout_reset_sbt(&adapter->timer_service, SBT_1S,
			    SBT_1S, ena_timer_service, (void *)adapter, 0);
		}

		ENA_FLAG_SET_ATOMIC(ENA_FLAG_DEV_UP, adapter);

		ena_unmask_all_io_irqs(adapter);
	}

	return (0);

err_up_complete:
	ena_destroy_all_io_queues(adapter);
err_io_que:
	ena_free_all_rx_resources(adapter);
err_setup_rx:
	ena_free_all_tx_resources(adapter);
err_setup_tx:
	ena_free_io_irq(adapter);
error:
	return (rc);
}