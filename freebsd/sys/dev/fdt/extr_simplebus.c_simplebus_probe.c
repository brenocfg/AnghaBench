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
 int /*<<< orphan*/ * ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_has_prop (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
simplebus_probe(device_t dev)
{
 
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	/*
	 * FDT data puts a "simple-bus" compatible string on many things that
	 * have children but aren't really buses in our world.  Without a
	 * ranges property we will fail to attach, so just fail to probe too.
	 */
	if (!(ofw_bus_is_compatible(dev, "simple-bus") &&
	    ofw_bus_has_prop(dev, "ranges")) &&
	    (ofw_bus_get_type(dev) == NULL || strcmp(ofw_bus_get_type(dev),
	     "soc") != 0))
		return (ENXIO);

	device_set_desc(dev, "Flattened device tree simple bus");

	return (BUS_PROBE_GENERIC);
}