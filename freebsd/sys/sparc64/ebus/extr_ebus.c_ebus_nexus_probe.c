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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char const* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
ebus_nexus_probe(device_t dev)
{
	const char* compat;

	compat = ofw_bus_get_compat(dev);
	if (compat != NULL && strcmp(ofw_bus_get_name(dev), "ebus") == 0 &&
	    strcmp(compat, "jbus-ebus") == 0) {
		device_set_desc(dev, "JBus-EBus bridge");
		return (BUS_PROBE_GENERIC);
	}
	return (ENXIO);
}