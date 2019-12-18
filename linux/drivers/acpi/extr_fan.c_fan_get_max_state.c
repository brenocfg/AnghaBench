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
struct thermal_cooling_device {struct acpi_device* devdata; } ;
struct acpi_fan {int fps_count; scalar_t__ acpi4; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_fan* acpi_driver_data (struct acpi_device*) ; 

__attribute__((used)) static int fan_get_max_state(struct thermal_cooling_device *cdev, unsigned long
			     *state)
{
	struct acpi_device *device = cdev->devdata;
	struct acpi_fan *fan = acpi_driver_data(device);

	if (fan->acpi4)
		*state = fan->fps_count - 1;
	else
		*state = 1;
	return 0;
}