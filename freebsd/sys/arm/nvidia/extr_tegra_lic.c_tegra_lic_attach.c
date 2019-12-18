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
struct tegra_lic_sc {int /*<<< orphan*/ ** mem_res; int /*<<< orphan*/ * parent; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  parent_xref ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LIC_CPU_IEP_CLASS ; 
 int /*<<< orphan*/  LIC_CPU_IER_CLR ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct tegra_lic_sc*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 struct tegra_lic_sc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lic_spec ; 
 int nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_lic_attach(device_t dev)
{
	struct tegra_lic_sc *sc;
	phandle_t node;
	phandle_t parent_xref;
	int i, rv;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	rv = OF_getencprop(node, "interrupt-parent", &parent_xref,
	    sizeof(parent_xref));
	if (rv <= 0) {
		device_printf(dev, "Cannot read parent node property\n");
		goto fail;
	}
	sc->parent = OF_device_from_xref(parent_xref);
	if (sc->parent == NULL) {
		device_printf(dev, "Cannott find parent controller\n");
		goto fail;
	}

	if (bus_alloc_resources(dev, lic_spec, sc->mem_res)) {
		device_printf(dev, "Cannott allocate resources\n");
		goto fail;
	}

	/* Disable all interrupts, route all to irq */
	for (i = 0; i < nitems(lic_spec); i++) {
		if (sc->mem_res[i] == NULL)
			continue;
		WR4(sc, i, LIC_CPU_IER_CLR, 0xFFFFFFFF);
		WR4(sc, i, LIC_CPU_IEP_CLASS, 0);
	}


	if (intr_pic_register(dev, OF_xref_from_node(node)) == NULL) {
		device_printf(dev, "Cannot register PIC\n");
		goto fail;
	}
	return (0);

fail:
	bus_release_resources(dev, lic_spec, sc->mem_res);
	return (ENXIO);
}