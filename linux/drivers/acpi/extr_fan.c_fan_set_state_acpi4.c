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
struct acpi_fan {unsigned long fps_count; TYPE_1__* fps; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
typedef  int acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int) ; 
 int EINVAL ; 
 struct acpi_fan* acpi_driver_data (struct acpi_device*) ; 
 int acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int fan_set_state_acpi4(struct acpi_device *device, unsigned long state)
{
	struct acpi_fan *fan = acpi_driver_data(device);
	acpi_status status;

	if (state >= fan->fps_count)
		return -EINVAL;

	status = acpi_execute_simple_method(device->handle, "_FSL",
					    fan->fps[state].control);
	if (ACPI_FAILURE(status)) {
		dev_dbg(&device->dev, "Failed to set state by _FSL\n");
		return status;
	}

	return 0;
}