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
struct TYPE_2__ {int dynamic_status; int removable; int ejectable; } ;
struct acpi_device {TYPE_1__ flags; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acpi_bus_get_flags(struct acpi_device *device)
{
	/* Presence of _STA indicates 'dynamic_status' */
	if (acpi_has_method(device->handle, "_STA"))
		device->flags.dynamic_status = 1;

	/* Presence of _RMV indicates 'removable' */
	if (acpi_has_method(device->handle, "_RMV"))
		device->flags.removable = 1;

	/* Presence of _EJD|_EJ0 indicates 'ejectable' */
	if (acpi_has_method(device->handle, "_EJD") ||
	    acpi_has_method(device->handle, "_EJ0"))
		device->flags.ejectable = 1;
}