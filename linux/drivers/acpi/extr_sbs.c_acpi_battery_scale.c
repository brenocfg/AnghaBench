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
struct acpi_battery {int dummy; } ;

/* Variables and functions */
 int acpi_battery_ipscale (struct acpi_battery*) ; 
 scalar_t__ acpi_battery_mode (struct acpi_battery*) ; 

__attribute__((used)) static inline int acpi_battery_scale(struct acpi_battery *battery)
{
	return (acpi_battery_mode(battery) ? 10 : 1) *
	    acpi_battery_ipscale(battery);
}