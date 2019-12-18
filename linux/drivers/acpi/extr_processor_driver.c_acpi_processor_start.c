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
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int ENODEV ; 
 int __acpi_processor_start (struct acpi_device*) ; 
 int /*<<< orphan*/  cpu_hotplug_disable () ; 
 int /*<<< orphan*/  cpu_hotplug_enable () ; 

__attribute__((used)) static int acpi_processor_start(struct device *dev)
{
	struct acpi_device *device = ACPI_COMPANION(dev);
	int ret;

	if (!device)
		return -ENODEV;

	/* Protect against concurrent CPU hotplug operations */
	cpu_hotplug_disable();
	ret = __acpi_processor_start(device);
	cpu_hotplug_enable();
	return ret;
}