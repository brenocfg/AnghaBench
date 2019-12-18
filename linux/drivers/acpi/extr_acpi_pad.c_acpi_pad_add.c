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
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PROCESSOR_AGGREGATOR_CLASS ; 
 int /*<<< orphan*/  ACPI_PROCESSOR_AGGREGATOR_DEVICE_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_device*) ; 
 scalar_t__ acpi_pad_add_sysfs (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_pad_notify ; 
 int /*<<< orphan*/  acpi_pad_remove_sysfs (struct acpi_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_pad_add(struct acpi_device *device)
{
	acpi_status status;

	strcpy(acpi_device_name(device), ACPI_PROCESSOR_AGGREGATOR_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_PROCESSOR_AGGREGATOR_CLASS);

	if (acpi_pad_add_sysfs(device))
		return -ENODEV;

	status = acpi_install_notify_handler(device->handle,
		ACPI_DEVICE_NOTIFY, acpi_pad_notify, device);
	if (ACPI_FAILURE(status)) {
		acpi_pad_remove_sysfs(device);
		return -ENODEV;
	}

	return 0;
}