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
struct padctl_softc {int /*<<< orphan*/  rst; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  dev; } ;
struct padctl_port {int (* init ) (struct padctl_softc*,struct padctl_port*) ;int name; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct padctl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_calibration (struct padctl_softc*) ; 
 int nitems (struct padctl_port*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int parse_fdt (struct padctl_softc*,int /*<<< orphan*/ ) ; 
 struct padctl_port* ports_tbl ; 
 int stub1 (struct padctl_softc*,struct padctl_port*) ; 

__attribute__((used)) static int
xusbpadctl_attach(device_t dev)
{
	struct padctl_softc * sc;
	int i, rid, rv;
	struct padctl_port *port;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		return (ENXIO);
	}

	rv = hwreset_get_by_ofw_name(dev, 0, "padctl", &sc->rst);
	if (rv != 0) {
		device_printf(dev, "Cannot get 'padctl' reset: %d\n", rv);
		return (rv);
	}
	rv = hwreset_deassert(sc->rst);
	if (rv != 0) {
		device_printf(dev, "Cannot unreset 'padctl' reset: %d\n", rv);
		return (rv);
	}

	load_calibration(sc);

	rv = parse_fdt(sc, node);
	if (rv != 0) {
		device_printf(dev, "Cannot parse fdt configuration: %d\n", rv);
		return (rv);
	}
	for (i = 0; i < nitems(ports_tbl); i++) {
		port = ports_tbl + i;
		if (!port->enabled)
			continue;
		if (port->init == NULL)
			continue;
		rv = port->init(sc, port);
		if (rv != 0) {
			device_printf(dev, "Cannot init port '%s'\n",
			    port->name);
			return (rv);
		}
	}
	return (0);
}