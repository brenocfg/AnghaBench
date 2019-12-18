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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_map_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ opal_check () ; 

__attribute__((used)) static int
opaldev_probe(device_t dev)
{
	phandle_t iparent;
	pcell_t *irqs;
	int i, n_irqs;

	if (!ofw_bus_is_compatible(dev, "ibm,opal-v3"))
		return (ENXIO);
	if (opal_check() != 0)
		return (ENXIO);

	device_set_desc(dev, "OPAL Abstraction Firmware");

	/* Manually add IRQs before attaching */
	if (OF_hasprop(ofw_bus_get_node(dev), "opal-interrupts")) {
		iparent = OF_finddevice("/interrupt-controller@0");
		iparent = OF_xref_from_node(iparent);

		n_irqs = OF_getproplen(ofw_bus_get_node(dev),
                    "opal-interrupts") / sizeof(*irqs);
		irqs = malloc(n_irqs * sizeof(*irqs), M_DEVBUF, M_WAITOK);
		OF_getencprop(ofw_bus_get_node(dev), "opal-interrupts", irqs,
		    n_irqs * sizeof(*irqs));
		for (i = 0; i < n_irqs; i++)
			bus_set_resource(dev, SYS_RES_IRQ, i,
			    ofw_bus_map_intr(dev, iparent, 1, &irqs[i]), 1);
		free(irqs, M_DEVBUF);
	}


	return (BUS_PROBE_SPECIFIC);
}