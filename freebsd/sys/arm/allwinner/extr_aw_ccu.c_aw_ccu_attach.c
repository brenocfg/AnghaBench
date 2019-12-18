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
struct aw_ccu_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int /*<<< orphan*/  ocd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCU_BASE ; 
 int /*<<< orphan*/  CCU_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 TYPE_1__* aw_ccu_search_compatible () ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_bus_tag (int /*<<< orphan*/ *) ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct aw_ccu_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplebus_add_device (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
aw_ccu_attach(device_t dev)
{
	struct aw_ccu_softc *sc;
	phandle_t node, child;
	device_t cdev;
	int error;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	simplebus_init(dev, node);

	sc->flags = aw_ccu_search_compatible()->ocd_data;

	/*
	 * Map registers. The DT doesn't have a "reg" property
	 * for the /clocks node and child nodes have conflicting "reg"
	 * properties.
	 */
	sc->bst = bus_get_bus_tag(dev);
	error = bus_space_map(sc->bst, CCU_BASE, CCU_SIZE, 0,
	    &sc->bsh);
	if (error != 0) {
		device_printf(dev, "couldn't map CCU: %d\n", error);
		return (error);
	}

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	/* Attach child devices */
	for (child = OF_child(node); child > 0; child = OF_peer(child)) {
		cdev = simplebus_add_device(dev, child, 0, NULL, -1, NULL);
		if (cdev != NULL)
			device_probe_and_attach(cdev);
	}

	return (bus_generic_attach(dev));
}