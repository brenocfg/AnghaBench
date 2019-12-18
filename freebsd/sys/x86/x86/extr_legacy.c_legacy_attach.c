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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  legacy_pci_cfgregopen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
legacy_attach(device_t dev)
{
	device_t child;

	legacy_pci_cfgregopen(dev);

	/*
	 * Let our child drivers identify any child devices that they
	 * can find.  Once that is done attach any devices that we
	 * found.
	 */
	bus_generic_probe(dev);
	bus_generic_attach(dev);

	/*
	 * If we didn't see ISA on a PCI bridge, add a top-level bus.
	 */
	if (!devclass_get_device(devclass_find("isa"), 0)) {
		child = BUS_ADD_CHILD(dev, 0, "isa", 0);
		if (child == NULL)
			panic("legacy_attach isa");
		device_probe_and_attach(child);
	}

	return 0;
}