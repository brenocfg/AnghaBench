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
typedef  int u32 ;
struct acpi_device {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; TYPE_2__* handler; } ;
struct TYPE_3__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {TYPE_1__ hotplug; } ;

/* Variables and functions */
#define  ACPI_NOTIFY_BUS_CHECK 131 
#define  ACPI_NOTIFY_DEVICE_CHECK 130 
#define  ACPI_NOTIFY_EJECT_REQUEST 129 
#define  ACPI_OST_EC_OSPM_EJECT 128 
 int /*<<< orphan*/  ACPI_OST_SC_EJECT_IN_PROGRESS ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  acpi_evaluate_ost (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int acpi_scan_bus_check (struct acpi_device*) ; 
 int acpi_scan_device_check (struct acpi_device*) ; 
 int acpi_scan_hot_remove (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int acpi_generic_hotplug_event(struct acpi_device *adev, u32 type)
{
	switch (type) {
	case ACPI_NOTIFY_BUS_CHECK:
		return acpi_scan_bus_check(adev);
	case ACPI_NOTIFY_DEVICE_CHECK:
		return acpi_scan_device_check(adev);
	case ACPI_NOTIFY_EJECT_REQUEST:
	case ACPI_OST_EC_OSPM_EJECT:
		if (adev->handler && !adev->handler->hotplug.enabled) {
			dev_info(&adev->dev, "Eject disabled\n");
			return -EPERM;
		}
		acpi_evaluate_ost(adev->handle, ACPI_NOTIFY_EJECT_REQUEST,
				  ACPI_OST_SC_EJECT_IN_PROGRESS, NULL);
		return acpi_scan_hot_remove(adev);
	}
	return -EINVAL;
}