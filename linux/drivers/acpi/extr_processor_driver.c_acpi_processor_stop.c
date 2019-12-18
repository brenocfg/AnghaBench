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
struct device {int dummy; } ;
struct acpi_processor {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_cppc_processor_exit (struct acpi_processor*) ; 
 struct acpi_processor* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_processor_notify ; 
 int /*<<< orphan*/  acpi_processor_power_exit (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_pss_perf_exit (struct acpi_processor*,struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_processor_stop(struct device *dev)
{
	struct acpi_device *device = ACPI_COMPANION(dev);
	struct acpi_processor *pr;

	if (!device)
		return 0;

	acpi_remove_notify_handler(device->handle, ACPI_DEVICE_NOTIFY,
				   acpi_processor_notify);

	pr = acpi_driver_data(device);
	if (!pr)
		return 0;
	acpi_processor_power_exit(pr);

	acpi_pss_perf_exit(pr, device);

	acpi_cppc_processor_exit(pr);

	return 0;
}