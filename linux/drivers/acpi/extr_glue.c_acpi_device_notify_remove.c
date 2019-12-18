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
struct device {int dummy; } ;
struct acpi_device {TYPE_1__* handler; } ;
struct acpi_bus_type {int /*<<< orphan*/  (* cleanup ) (struct device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  (* unbind ) (struct device*) ;} ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 struct acpi_bus_type* acpi_get_bus_type (struct device*) ; 
 int /*<<< orphan*/  acpi_unbind_one (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 

__attribute__((used)) static int acpi_device_notify_remove(struct device *dev)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);
	struct acpi_bus_type *type;

	if (!adev)
		return 0;

	type = acpi_get_bus_type(dev);
	if (type && type->cleanup)
		type->cleanup(dev);
	else if (adev->handler && adev->handler->unbind)
		adev->handler->unbind(dev);

	acpi_unbind_one(dev);
	return 0;
}