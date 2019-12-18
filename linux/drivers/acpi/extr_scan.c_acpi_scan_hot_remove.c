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
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__* handler; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {scalar_t__ demand_offline; } ;
struct TYPE_3__ {TYPE_2__ hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 unsigned long long ACPI_STA_DEVICE_ENABLED ; 
 scalar_t__ AE_NOT_FOUND ; 
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_bus_trim (struct acpi_device*) ; 
 scalar_t__ acpi_evaluate_ej0 (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_evaluate_lck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_handle_warn (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  acpi_scan_is_offline (struct acpi_device*,int) ; 
 int acpi_scan_try_to_offline (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_scan_hot_remove(struct acpi_device *device)
{
	acpi_handle handle = device->handle;
	unsigned long long sta;
	acpi_status status;

	if (device->handler && device->handler->hotplug.demand_offline) {
		if (!acpi_scan_is_offline(device, true))
			return -EBUSY;
	} else {
		int error = acpi_scan_try_to_offline(device);
		if (error)
			return error;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
		"Hot-removing device %s...\n", dev_name(&device->dev)));

	acpi_bus_trim(device);

	acpi_evaluate_lck(handle, 0);
	/*
	 * TBD: _EJD support.
	 */
	status = acpi_evaluate_ej0(handle);
	if (status == AE_NOT_FOUND)
		return -ENODEV;
	else if (ACPI_FAILURE(status))
		return -EIO;

	/*
	 * Verify if eject was indeed successful.  If not, log an error
	 * message.  No need to call _OST since _EJ0 call was made OK.
	 */
	status = acpi_evaluate_integer(handle, "_STA", NULL, &sta);
	if (ACPI_FAILURE(status)) {
		acpi_handle_warn(handle,
			"Status check after eject failed (0x%x)\n", status);
	} else if (sta & ACPI_STA_DEVICE_ENABLED) {
		acpi_handle_warn(handle,
			"Eject incomplete - status 0x%llx\n", sta);
	}

	return 0;
}