#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  valid; } ;
struct TYPE_4__ {scalar_t__ prepare_count; TYPE_1__ flags; } ;
struct acpi_device {TYPE_2__ wakeup; int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int acpi_bus_extract_wakeup_device_power_package (struct acpi_device*) ; 
 int acpi_device_sleep_wake (struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_wakeup_gpe_init (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void acpi_bus_get_wakeup_device_flags(struct acpi_device *device)
{
	int err;

	/* Presence of _PRW indicates wake capable */
	if (!acpi_has_method(device->handle, "_PRW"))
		return;

	err = acpi_bus_extract_wakeup_device_power_package(device);
	if (err) {
		dev_err(&device->dev, "_PRW evaluation error: %d\n", err);
		return;
	}

	device->wakeup.flags.valid = acpi_wakeup_gpe_init(device);
	device->wakeup.prepare_count = 0;
	/*
	 * Call _PSW/_DSW object to disable its ability to wake the sleeping
	 * system for the ACPI device with the _PRW object.
	 * The _PSW object is deprecated in ACPI 3.0 and is replaced by _DSW.
	 * So it is necessary to call _DSW object first. Only when it is not
	 * present will the _PSW object used.
	 */
	err = acpi_device_sleep_wake(device, 0, 0, 0);
	if (err)
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				"error in _DSW or _PSW evaluation\n"));
}