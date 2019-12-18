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
typedef  int u_int ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
acpi_battery_find_dev(u_int logical_unit)
{
    int found_unit, i, maxunit;
    device_t dev;
    devclass_t batt_dc;

    dev = NULL;
    found_unit = 0;
    batt_dc = devclass_find("battery");
    maxunit = devclass_get_maxunit(batt_dc);
    for (i = 0; i < maxunit; i++) {
	dev = devclass_get_device(batt_dc, i);
	if (dev == NULL)
	    continue;
	if (logical_unit == found_unit)
	    break;
	found_unit++;
	dev = NULL;
    }

    return (dev);
}