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
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_pir_probe (int,int /*<<< orphan*/ ) ; 
 int pcib_get_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
legacy_pcib_attach(device_t dev)
{
#ifdef __HAVE_PIR
	device_t pir;
#endif
	int bus;

	bus = pcib_get_bus(dev);
#ifdef __HAVE_PIR
	/*
	 * Look for a PCI BIOS interrupt routing table as that will be
	 * our method of routing interrupts if we have one.
	 */
	if (pci_pir_probe(bus, 0)) {
		pir = BUS_ADD_CHILD(device_get_parent(dev), 0, "pir", 0);
		if (pir != NULL)
			device_probe_and_attach(pir);
	}
#endif
	device_add_child(dev, "pci", -1);
	return bus_generic_attach(dev);
}