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
struct TYPE_2__ {int /*<<< orphan*/  enumeration_by_parent; } ;
struct acpi_device {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RECONFIG_DEVICE_ADD ; 
 int /*<<< orphan*/  acpi_create_platform_device (struct acpi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_device_set_enumerated (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_reconfig_chain ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_device*) ; 

__attribute__((used)) static void acpi_default_enumeration(struct acpi_device *device)
{
	/*
	 * Do not enumerate devices with enumeration_by_parent flag set as
	 * they will be enumerated by their respective parents.
	 */
	if (!device->flags.enumeration_by_parent) {
		acpi_create_platform_device(device, NULL);
		acpi_device_set_enumerated(device);
	} else {
		blocking_notifier_call_chain(&acpi_reconfig_chain,
					     ACPI_RECONFIG_DEVICE_ADD, device);
	}
}