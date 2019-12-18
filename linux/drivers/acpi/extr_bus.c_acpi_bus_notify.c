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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* notify ) (struct acpi_device*,int /*<<< orphan*/ ) ;} ;
struct acpi_driver {int flags; TYPE_1__ ops; } ;
struct acpi_device {struct acpi_driver* driver; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_DRIVER_ALL_NOTIFY_EVENTS ; 
#define  ACPI_NOTIFY_BUS_CHECK 135 
#define  ACPI_NOTIFY_BUS_MODE_MISMATCH 134 
#define  ACPI_NOTIFY_DEVICE_CHECK 133 
#define  ACPI_NOTIFY_DEVICE_CHECK_LIGHT 132 
#define  ACPI_NOTIFY_DEVICE_WAKE 131 
#define  ACPI_NOTIFY_EJECT_REQUEST 130 
#define  ACPI_NOTIFY_FREQUENCY_MISMATCH 129 
#define  ACPI_NOTIFY_POWER_FAULT 128 
 int /*<<< orphan*/  ACPI_OST_SC_NON_SPECIFIC_FAILURE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 struct acpi_device* acpi_bus_get_acpi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_bus_put_acpi_device (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_evaluate_ost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_hotplug_schedule (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct acpi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_bus_notify(acpi_handle handle, u32 type, void *data)
{
	struct acpi_device *adev;
	struct acpi_driver *driver;
	u32 ost_code = ACPI_OST_SC_NON_SPECIFIC_FAILURE;
	bool hotplug_event = false;

	switch (type) {
	case ACPI_NOTIFY_BUS_CHECK:
		acpi_handle_debug(handle, "ACPI_NOTIFY_BUS_CHECK event\n");
		hotplug_event = true;
		break;

	case ACPI_NOTIFY_DEVICE_CHECK:
		acpi_handle_debug(handle, "ACPI_NOTIFY_DEVICE_CHECK event\n");
		hotplug_event = true;
		break;

	case ACPI_NOTIFY_DEVICE_WAKE:
		acpi_handle_debug(handle, "ACPI_NOTIFY_DEVICE_WAKE event\n");
		break;

	case ACPI_NOTIFY_EJECT_REQUEST:
		acpi_handle_debug(handle, "ACPI_NOTIFY_EJECT_REQUEST event\n");
		hotplug_event = true;
		break;

	case ACPI_NOTIFY_DEVICE_CHECK_LIGHT:
		acpi_handle_debug(handle, "ACPI_NOTIFY_DEVICE_CHECK_LIGHT event\n");
		/* TBD: Exactly what does 'light' mean? */
		break;

	case ACPI_NOTIFY_FREQUENCY_MISMATCH:
		acpi_handle_err(handle, "Device cannot be configured due "
				"to a frequency mismatch\n");
		break;

	case ACPI_NOTIFY_BUS_MODE_MISMATCH:
		acpi_handle_err(handle, "Device cannot be configured due "
				"to a bus mode mismatch\n");
		break;

	case ACPI_NOTIFY_POWER_FAULT:
		acpi_handle_err(handle, "Device has suffered a power fault\n");
		break;

	default:
		acpi_handle_debug(handle, "Unknown event type 0x%x\n", type);
		break;
	}

	adev = acpi_bus_get_acpi_device(handle);
	if (!adev)
		goto err;

	driver = adev->driver;
	if (driver && driver->ops.notify &&
	    (driver->flags & ACPI_DRIVER_ALL_NOTIFY_EVENTS))
		driver->ops.notify(adev, type);

	if (!hotplug_event) {
		acpi_bus_put_acpi_device(adev);
		return;
	}

	if (ACPI_SUCCESS(acpi_hotplug_schedule(adev, type)))
		return;

	acpi_bus_put_acpi_device(adev);

 err:
	acpi_evaluate_ost(handle, type, ost_code, NULL);
}