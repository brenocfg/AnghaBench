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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (TYPE_1__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  dptf_power_attribute_group ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct acpi_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dptf_power_add(struct platform_device *pdev)
{
	struct acpi_device *acpi_dev;
	acpi_status status;
	unsigned long long ptype;
	int result;

	acpi_dev = ACPI_COMPANION(&(pdev->dev));
	if (!acpi_dev)
		return -ENODEV;

	status = acpi_evaluate_integer(acpi_dev->handle, "PTYP", NULL, &ptype);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	if (ptype != 0x11)
		return -ENODEV;

	result = sysfs_create_group(&pdev->dev.kobj,
				    &dptf_power_attribute_group);
	if (result)
		return result;

	platform_set_drvdata(pdev, acpi_dev);

	return 0;
}