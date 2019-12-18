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
struct acpi_thermal {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int acpi_thermal_set_cooling_mode(struct acpi_thermal *tz, int mode)
{
	if (!tz)
		return -EINVAL;

	if (ACPI_FAILURE(acpi_execute_simple_method(tz->device->handle,
						    "_SCP", mode)))
		return -ENODEV;

	return 0;
}