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
struct omap4_wugen_sc {int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/ * sc_parent; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  parent_xref ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct omap4_wugen_sc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_wugen_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap4_wugen_attach(device_t dev)
{
	struct omap4_wugen_sc *sc;
	phandle_t node;
	phandle_t parent_xref;
	int rid, rv;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	node = ofw_bus_get_node(dev);

	rv = OF_getencprop(node, "interrupt-parent", &parent_xref,
	    sizeof(parent_xref));
	if (rv <= 0) {
		device_printf(dev, "can't read parent node property\n");
		goto fail;
	}
	sc->sc_parent = OF_device_from_xref(parent_xref);
	if (sc->sc_parent == NULL) {
		device_printf(dev, "can't find parent controller\n");
		goto fail;
	}

	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "can't allocate resources\n");
		return (ENXIO);
	}

	if (intr_pic_register(dev, OF_xref_from_node(node)) == NULL) {
		device_printf(dev, "can't register PIC\n");
		goto fail;
	}
	return (0);

fail:
	omap4_wugen_detach(dev);
	return (ENXIO);
}