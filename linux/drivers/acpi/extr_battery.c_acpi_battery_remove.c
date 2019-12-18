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
struct acpi_device {int /*<<< orphan*/  dev; } ;
struct acpi_battery {int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_nb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_battery_remove_fs (struct acpi_device*) ; 
 struct acpi_battery* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_battery*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_battery (struct acpi_battery*) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_battery_remove(struct acpi_device *device)
{
	struct acpi_battery *battery = NULL;

	if (!device || !acpi_driver_data(device))
		return -EINVAL;
	device_init_wakeup(&device->dev, 0);
	battery = acpi_driver_data(device);
	unregister_pm_notifier(&battery->pm_nb);
#ifdef CONFIG_ACPI_PROCFS_POWER
	acpi_battery_remove_fs(device);
#endif
	sysfs_remove_battery(battery);
	mutex_destroy(&battery->lock);
	mutex_destroy(&battery->sysfs_lock);
	kfree(battery);
	return 0;
}