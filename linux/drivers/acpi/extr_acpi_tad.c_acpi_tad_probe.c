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
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct acpi_tad_driver_data {unsigned long long capabilities; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 unsigned long long ACPI_TAD_AC_WAKE ; 
 unsigned long long ACPI_TAD_DC_WAKE ; 
 unsigned long long ACPI_TAD_RT ; 
 int DPM_FLAG_LEAVE_SUSPENDED ; 
 int DPM_FLAG_SMART_SUSPEND ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_tad_attr_group ; 
 int /*<<< orphan*/  acpi_tad_dc_attr_group ; 
 int /*<<< orphan*/  acpi_tad_remove (struct platform_device*) ; 
 int /*<<< orphan*/  acpi_tad_time_attr_group ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (struct device*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct acpi_tad_driver_data*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct acpi_tad_driver_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_suspend (struct device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_tad_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	acpi_handle handle = ACPI_HANDLE(dev);
	struct acpi_tad_driver_data *dd;
	acpi_status status;
	unsigned long long caps;
	int ret;

	/*
	 * Initialization failure messages are mostly about firmware issues, so
	 * print them at the "info" level.
	 */
	status = acpi_evaluate_integer(handle, "_GCP", NULL, &caps);
	if (ACPI_FAILURE(status)) {
		dev_info(dev, "Unable to get capabilities\n");
		return -ENODEV;
	}

	if (!(caps & ACPI_TAD_AC_WAKE)) {
		dev_info(dev, "Unsupported capabilities\n");
		return -ENODEV;
	}

	if (!acpi_has_method(handle, "_PRW")) {
		dev_info(dev, "Missing _PRW\n");
		return -ENODEV;
	}

	dd = devm_kzalloc(dev, sizeof(*dd), GFP_KERNEL);
	if (!dd)
		return -ENOMEM;

	dd->capabilities = caps;
	dev_set_drvdata(dev, dd);

	/*
	 * Assume that the ACPI PM domain has been attached to the device and
	 * simply enable system wakeup and runtime PM and put the device into
	 * runtime suspend.  Everything else should be taken care of by the ACPI
	 * PM domain callbacks.
	 */
	device_init_wakeup(dev, true);
	dev_pm_set_driver_flags(dev, DPM_FLAG_SMART_SUSPEND |
				     DPM_FLAG_LEAVE_SUSPENDED);
	/*
	 * The platform bus type layer tells the ACPI PM domain powers up the
	 * device, so set the runtime PM status of it to "active".
	 */
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_suspend(dev);

	ret = sysfs_create_group(&dev->kobj, &acpi_tad_attr_group);
	if (ret)
		goto fail;

	if (caps & ACPI_TAD_DC_WAKE) {
		ret = sysfs_create_group(&dev->kobj, &acpi_tad_dc_attr_group);
		if (ret)
			goto fail;
	}

	if (caps & ACPI_TAD_RT) {
		ret = sysfs_create_group(&dev->kobj, &acpi_tad_time_attr_group);
		if (ret)
			goto fail;
	}

	return 0;

fail:
	acpi_tad_remove(pdev);
	return ret;
}