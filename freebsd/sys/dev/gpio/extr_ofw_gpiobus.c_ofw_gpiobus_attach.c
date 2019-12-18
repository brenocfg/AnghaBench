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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int gpiobus_init_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ofw_gpiobus_add_fdt_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
ofw_gpiobus_attach(device_t dev)
{
	int err;
	phandle_t child;

	err = gpiobus_init_softc(dev);
	if (err != 0)
		return (err);
	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	/*
	 * Attach the children represented in the device tree.
	 */
	for (child = OF_child(ofw_bus_get_node(dev)); child != 0;
	    child = OF_peer(child)) {
		if (!OF_hasprop(child, "gpios"))
			continue;
		if (ofw_gpiobus_add_fdt_child(dev, NULL, child) == NULL)
			continue;
	}

	return (bus_generic_attach(dev));
}