#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int acells; int scells; } ;
struct simple_mfd_softc {int /*<<< orphan*/ * syscon; int /*<<< orphan*/ * mem_res; TYPE_1__ sc; int /*<<< orphan*/ * dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCON_LOCK_INIT (struct simple_mfd_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 struct simple_mfd_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * simple_mfd_add_device (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_mfd_syscon_class ; 
 scalar_t__ simplebus_fill_ranges (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/ * syscon_create_ofw_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
simple_mfd_attach(device_t dev)
{
	struct simple_mfd_softc *sc;
	phandle_t node, child;
	device_t cdev;
	int rid;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	sc->dev = dev;
	rid = 0;

	/* Parse address-cells and size-cells from the parent node as a fallback */
	if (OF_getencprop(node, "#address-cells", &sc->sc.acells,
	    sizeof(sc->sc.acells)) == -1) {
		if (OF_getencprop(OF_parent(node), "#address-cells", &sc->sc.acells,
		    sizeof(sc->sc.acells)) == -1) {
			sc->sc.acells = 2;
		}
	}
	if (OF_getencprop(node, "#size-cells", &sc->sc.scells,
	    sizeof(sc->sc.scells)) == -1) {
		if (OF_getencprop(OF_parent(node), "#size-cells", &sc->sc.scells,
		    sizeof(sc->sc.scells)) == -1) {
			sc->sc.scells = 1;
		}
	}

	/* If the node has a ranges prop, parse it so children mapping will be done correctly */
	if (OF_hasprop(node, "ranges")) {
		if (simplebus_fill_ranges(node, &sc->sc) < 0) {
			device_printf(dev, "could not get ranges\n");
			return (ENXIO);
		}
	}

	/* Attach child devices */
	for (child = OF_child(node); child > 0; child = OF_peer(child)) {
		cdev = simple_mfd_add_device(dev, child, 0, NULL, -1, NULL);
		if (cdev != NULL)
			device_probe_and_attach(cdev);
	}

	if (ofw_bus_is_compatible(dev, "syscon")) {
		sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
		    RF_ACTIVE);
		if (sc->mem_res == NULL) {
			device_printf(dev,
			    "Cannot allocate memory resource\n");
			return (ENXIO);
		}

		SYSCON_LOCK_INIT(sc);
		sc->syscon = syscon_create_ofw_node(dev,
		    &simple_mfd_syscon_class, ofw_bus_get_node(dev));
		if (sc->syscon == NULL) {
			device_printf(dev,
			    "Failed to create/register syscon\n");
			return (ENXIO);
		}
	}
	return (bus_generic_attach(dev));
}