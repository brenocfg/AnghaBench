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
struct acpi_device {int dummy; } ;
struct acpi_ac {int /*<<< orphan*/  battery_nb; int /*<<< orphan*/  charger; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_ac_remove_fs (struct acpi_ac*) ; 
 struct acpi_ac* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  kfree (struct acpi_ac*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_acpi_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_ac_remove(struct acpi_device *device)
{
	struct acpi_ac *ac = NULL;


	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	ac = acpi_driver_data(device);

	power_supply_unregister(ac->charger);
	unregister_acpi_notifier(&ac->battery_nb);

#ifdef CONFIG_ACPI_PROCFS_POWER
	acpi_ac_remove_fs(ac);
#endif

	kfree(ac);

	return 0;
}