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
struct ena_com_dev_get_features_ctx {int dummy; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int wd_active; int /*<<< orphan*/  timer_service; int /*<<< orphan*/  keep_alive_timestamp; int /*<<< orphan*/  num_queues; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ifp; struct ena_com_dev* ena_dev; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_CLEAR_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_DEV_UP_BEFORE_RESET ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_LINK_UP ; 
 int /*<<< orphan*/  ENA_FLAG_ONGOING_RESET ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_REGS_RESET_DRIVER_INVALID_STATE ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  SBT_1S ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ena_com_abort_admin_commands (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_admin_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_dev_reset (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_wait_for_abort_completion (struct ena_com_dev*) ; 
 int ena_device_init (struct ena_adapter*,int /*<<< orphan*/ ,struct ena_com_dev_get_features_ctx*,int*) ; 
 int ena_device_validate_params (struct ena_adapter*,struct ena_com_dev_get_features_ctx*) ; 
 int /*<<< orphan*/  ena_disable_msix (struct ena_adapter*) ; 
 int ena_enable_msix_and_set_admin_interrupts (struct ena_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_free_mgmnt_irq (struct ena_adapter*) ; 
 int ena_handle_updated_queues (struct ena_adapter*,struct ena_com_dev_get_features_ctx*) ; 
 int /*<<< orphan*/  ena_timer_service ; 
 int ena_up (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_version ; 
 int /*<<< orphan*/  getsbinuptime () ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ena_restore_device(struct ena_adapter *adapter)
{
	struct ena_com_dev_get_features_ctx get_feat_ctx;
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	if_t ifp = adapter->ifp;
	device_t dev = adapter->pdev;
	int wd_active;
	int rc;

	ENA_FLAG_SET_ATOMIC(ENA_FLAG_ONGOING_RESET, adapter);

	rc = ena_device_init(adapter, dev, &get_feat_ctx, &wd_active);
	if (rc != 0) {
		device_printf(dev, "Cannot initialize device\n");
		goto err;
	}
	/*
	 * Only enable WD if it was enabled before reset, so it won't override
	 * value set by the user by the sysctl.
	 */
	if (adapter->wd_active != 0)
		adapter->wd_active = wd_active;

	rc = ena_device_validate_params(adapter, &get_feat_ctx);
	if (rc != 0) {
		device_printf(dev, "Validation of device parameters failed\n");
		goto err_device_destroy;
	}

	rc = ena_handle_updated_queues(adapter, &get_feat_ctx);
	if (rc != 0)
		goto err_device_destroy;

	ENA_FLAG_CLEAR_ATOMIC(ENA_FLAG_ONGOING_RESET, adapter);
	/* Make sure we don't have a race with AENQ Links state handler */
	if (ENA_FLAG_ISSET(ENA_FLAG_LINK_UP, adapter))
		if_link_state_change(ifp, LINK_STATE_UP);

	rc = ena_enable_msix_and_set_admin_interrupts(adapter,
	    adapter->num_queues);
	if (rc != 0) {
		device_printf(dev, "Enable MSI-X failed\n");
		goto err_device_destroy;
	}

	/* If the interface was up before the reset bring it up */
	if (ENA_FLAG_ISSET(ENA_FLAG_DEV_UP_BEFORE_RESET, adapter)) {
		rc = ena_up(adapter);
		if (rc != 0) {
			device_printf(dev, "Failed to create I/O queues\n");
			goto err_disable_msix;
		}
	}

	/* Indicate that device is running again and ready to work */
	ENA_FLAG_SET_ATOMIC(ENA_FLAG_DEVICE_RUNNING, adapter);

	if (ENA_FLAG_ISSET(ENA_FLAG_DEV_UP_BEFORE_RESET, adapter)) {
		/*
		 * As the AENQ handlers weren't executed during reset because
		 * the flag ENA_FLAG_DEVICE_RUNNING was turned off, the
		 * timestamp must be updated again That will prevent next reset
		 * caused by missing keep alive.
		 */
		adapter->keep_alive_timestamp = getsbinuptime();
		callout_reset_sbt(&adapter->timer_service, SBT_1S, SBT_1S,
		    ena_timer_service, (void *)adapter, 0);
	}

	device_printf(dev,
	    "Device reset completed successfully, Driver info: %s\n", ena_version);

	return (rc);

err_disable_msix:
	ena_free_mgmnt_irq(adapter);
	ena_disable_msix(adapter);
err_device_destroy:
	ena_com_abort_admin_commands(ena_dev);
	ena_com_wait_for_abort_completion(ena_dev);
	ena_com_admin_destroy(ena_dev);
	ena_com_dev_reset(ena_dev, ENA_REGS_RESET_DRIVER_INVALID_STATE);
	ena_com_mmio_reg_read_request_destroy(ena_dev);
err:
	ENA_FLAG_CLEAR_ATOMIC(ENA_FLAG_DEVICE_RUNNING, adapter);
	ENA_FLAG_CLEAR_ATOMIC(ENA_FLAG_ONGOING_RESET, adapter);
	device_printf(dev, "Reset attempt failed. Can not reset the device\n");

	return (rc);
}