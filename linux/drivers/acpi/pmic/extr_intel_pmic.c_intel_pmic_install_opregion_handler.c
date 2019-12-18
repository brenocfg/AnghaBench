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
struct regmap {int dummy; } ;
struct intel_pmic_opregion_data {int dummy; } ;
struct intel_pmic_opregion {int /*<<< orphan*/  lpat_table; struct intel_pmic_opregion_data* data; struct regmap* regmap; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PMIC_POWER_OPREGION_ID ; 
 int /*<<< orphan*/  PMIC_REGS_OPREGION_ID ; 
 int /*<<< orphan*/  PMIC_THERMAL_OPREGION_ID ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct intel_pmic_opregion*) ; 
 int /*<<< orphan*/  acpi_lpat_free_conversion_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_lpat_get_conversion_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_pmic_opregion* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct intel_pmic_opregion* intel_pmic_opregion ; 
 int /*<<< orphan*/  intel_pmic_power_handler ; 
 int /*<<< orphan*/  intel_pmic_regs_handler ; 
 int /*<<< orphan*/  intel_pmic_thermal_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int intel_pmic_install_opregion_handler(struct device *dev, acpi_handle handle,
					struct regmap *regmap,
					struct intel_pmic_opregion_data *d)
{
	acpi_status status;
	struct intel_pmic_opregion *opregion;
	int ret;

	if (!dev || !regmap || !d)
		return -EINVAL;

	if (!handle)
		return -ENODEV;

	opregion = devm_kzalloc(dev, sizeof(*opregion), GFP_KERNEL);
	if (!opregion)
		return -ENOMEM;

	mutex_init(&opregion->lock);
	opregion->regmap = regmap;
	opregion->lpat_table = acpi_lpat_get_conversion_table(handle);

	status = acpi_install_address_space_handler(handle,
						    PMIC_POWER_OPREGION_ID,
						    intel_pmic_power_handler,
						    NULL, opregion);
	if (ACPI_FAILURE(status)) {
		ret = -ENODEV;
		goto out_error;
	}

	status = acpi_install_address_space_handler(handle,
						    PMIC_THERMAL_OPREGION_ID,
						    intel_pmic_thermal_handler,
						    NULL, opregion);
	if (ACPI_FAILURE(status)) {
		ret = -ENODEV;
		goto out_remove_power_handler;
	}

	status = acpi_install_address_space_handler(handle,
			PMIC_REGS_OPREGION_ID, intel_pmic_regs_handler, NULL,
			opregion);
	if (ACPI_FAILURE(status)) {
		ret = -ENODEV;
		goto out_remove_thermal_handler;
	}

	opregion->data = d;
	intel_pmic_opregion = opregion;
	return 0;

out_remove_thermal_handler:
	acpi_remove_address_space_handler(handle, PMIC_THERMAL_OPREGION_ID,
					  intel_pmic_thermal_handler);

out_remove_power_handler:
	acpi_remove_address_space_handler(handle, PMIC_POWER_OPREGION_ID,
					  intel_pmic_power_handler);

out_error:
	acpi_lpat_free_conversion_table(opregion->lpat_table);
	return ret;
}