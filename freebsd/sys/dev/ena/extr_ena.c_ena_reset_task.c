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
struct ena_adapter {int /*<<< orphan*/  ioctl_sx; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ena_destroy_device (struct ena_adapter*,int) ; 
 int /*<<< orphan*/  ena_restore_device (struct ena_adapter*) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ena_reset_task(void *arg, int pending)
{
	struct ena_adapter *adapter = (struct ena_adapter *)arg;

	if (unlikely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))) {
		device_printf(adapter->pdev,
		    "device reset scheduled but trigger_reset is off\n");
		return;
	}

	sx_xlock(&adapter->ioctl_sx);
	ena_destroy_device(adapter, false);
	ena_restore_device(adapter);
	sx_unlock(&adapter->ioctl_sx);
}