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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int acpi_bay_match (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_device_is_battery (struct acpi_device*) ; 
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool is_ejectable_bay(struct acpi_device *adev)
{
	acpi_handle handle = adev->handle;

	if (acpi_has_method(handle, "_EJ0") && acpi_device_is_battery(adev))
		return true;

	return acpi_bay_match(handle);
}