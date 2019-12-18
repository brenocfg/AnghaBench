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
struct acpi_sbs {int manager_present; int batteries_supported; int /*<<< orphan*/  hc; struct acpi_device* device; int /*<<< orphan*/  lock; } ;
struct acpi_device {struct acpi_sbs* driver_data; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SBS_CLASS ; 
 int /*<<< orphan*/  ACPI_SBS_DEVICE_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SBS_BAT ; 
 int /*<<< orphan*/  acpi_battery_add (struct acpi_sbs*,int) ; 
 int acpi_charger_add (struct acpi_sbs*) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_driver_data (int /*<<< orphan*/ ) ; 
 int acpi_manager_get_info (struct acpi_sbs*) ; 
 int /*<<< orphan*/  acpi_sbs_callback ; 
 int /*<<< orphan*/  acpi_sbs_remove (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_smbus_register_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_sbs*) ; 
 struct acpi_sbs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_apple_machine ; 

__attribute__((used)) static int acpi_sbs_add(struct acpi_device *device)
{
	struct acpi_sbs *sbs;
	int result = 0;
	int id;

	sbs = kzalloc(sizeof(struct acpi_sbs), GFP_KERNEL);
	if (!sbs) {
		result = -ENOMEM;
		goto end;
	}

	mutex_init(&sbs->lock);

	sbs->hc = acpi_driver_data(device->parent);
	sbs->device = device;
	strcpy(acpi_device_name(device), ACPI_SBS_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_SBS_CLASS);
	device->driver_data = sbs;

	result = acpi_charger_add(sbs);
	if (result && result != -ENODEV)
		goto end;

	result = 0;

	if (!x86_apple_machine) {
		result = acpi_manager_get_info(sbs);
		if (!result) {
			sbs->manager_present = 1;
			for (id = 0; id < MAX_SBS_BAT; ++id)
				if ((sbs->batteries_supported & (1 << id)))
					acpi_battery_add(sbs, id);
		}
	}

	if (!sbs->manager_present)
		acpi_battery_add(sbs, 0);

	acpi_smbus_register_callback(sbs->hc, acpi_sbs_callback, sbs);
      end:
	if (result)
		acpi_sbs_remove(device);
	return result;
}