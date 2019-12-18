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
struct acpi_battery {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_INFO ; 
 int ENODEV ; 
 scalar_t__ acpi_bus_get_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_battery_get_status(struct acpi_battery *battery)
{
	if (acpi_bus_get_status(battery->device)) {
		ACPI_EXCEPTION((AE_INFO, AE_ERROR, "Evaluating _STA"));
		return -ENODEV;
	}
	return 0;
}