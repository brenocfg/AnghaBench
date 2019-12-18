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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RTC_DESC ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
rtc_ebus_probe(device_t dev)
{

	if (strcmp(ofw_bus_get_name(dev), "rtc") == 0) {
		/* The bq4802 is not supported, yet. */
		if (ofw_bus_get_compat(dev) != NULL &&
		    strcmp(ofw_bus_get_compat(dev), "bq4802") == 0)
			return (ENXIO);
		device_set_desc(dev, RTC_DESC);
		return (0);
	}

	return (ENXIO);
}