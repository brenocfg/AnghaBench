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
struct acpi_battery {int spec; } ;

/* Variables and functions */
 int battery_scale (int) ; 

__attribute__((used)) static inline int acpi_battery_vscale(struct acpi_battery *battery)
{
	return battery_scale((battery->spec & 0x0f00) >> 8);
}