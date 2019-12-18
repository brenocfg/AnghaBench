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
struct acpi_battery {scalar_t__ full_charge_capacity; scalar_t__ design_capacity; } ;

/* Variables and functions */

__attribute__((used)) static bool acpi_battery_is_degraded(struct acpi_battery *battery)
{
	return battery->full_charge_capacity && battery->design_capacity &&
		battery->full_charge_capacity < battery->design_capacity;
}