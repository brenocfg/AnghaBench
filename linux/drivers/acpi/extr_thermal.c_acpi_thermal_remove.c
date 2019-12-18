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
struct acpi_thermal {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_thermal* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_thermal_pm_queue ; 
 int /*<<< orphan*/  acpi_thermal_unregister_thermal_zone (struct acpi_thermal*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_thermal*) ; 

__attribute__((used)) static int acpi_thermal_remove(struct acpi_device *device)
{
	struct acpi_thermal *tz = NULL;

	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	flush_workqueue(acpi_thermal_pm_queue);
	tz = acpi_driver_data(device);

	acpi_thermal_unregister_thermal_zone(tz);
	kfree(tz);
	return 0;
}