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
struct TYPE_2__ {int match_driver; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_STA_DEFAULT ; 
 int acpi_add_single_object (struct acpi_device**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int device_attach (int /*<<< orphan*/ *) ; 

int acpi_bus_register_early_device(int type)
{
	struct acpi_device *device = NULL;
	int result;

	result = acpi_add_single_object(&device, NULL,
					type, ACPI_STA_DEFAULT);
	if (result)
		return result;

	device->flags.match_driver = true;
	return device_attach(&device->dev);
}