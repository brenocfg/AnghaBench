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
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int devclass_get_count (int /*<<< orphan*/ *) ; 

int
acpi_battery_get_units(void)
{
    devclass_t batt_dc;

    batt_dc = devclass_find("battery");
    if (batt_dc == NULL)
	return (0);
    return (devclass_get_count(batt_dc));
}