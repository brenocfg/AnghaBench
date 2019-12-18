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
struct TYPE_2__ {scalar_t__ functional; scalar_t__ present; } ;
struct acpi_device {int /*<<< orphan*/  dev; scalar_t__ handler; int /*<<< orphan*/  handle; TYPE_1__ status; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_bus_get_status (struct acpi_device*) ; 
 int acpi_bus_scan (int /*<<< orphan*/ ) ; 
 int acpi_scan_device_not_present (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int acpi_scan_device_check(struct acpi_device *adev)
{
	int error;

	acpi_bus_get_status(adev);
	if (adev->status.present || adev->status.functional) {
		/*
		 * This function is only called for device objects for which
		 * matching scan handlers exist.  The only situation in which
		 * the scan handler is not attached to this device object yet
		 * is when the device has just appeared (either it wasn't
		 * present at all before or it was removed and then added
		 * again).
		 */
		if (adev->handler) {
			dev_warn(&adev->dev, "Already enumerated\n");
			return -EALREADY;
		}
		error = acpi_bus_scan(adev->handle);
		if (error) {
			dev_warn(&adev->dev, "Namespace scan failure\n");
			return error;
		}
		if (!adev->handler) {
			dev_warn(&adev->dev, "Enumeration failure\n");
			error = -ENODEV;
		}
	} else {
		error = acpi_scan_device_not_present(adev);
	}
	return error;
}