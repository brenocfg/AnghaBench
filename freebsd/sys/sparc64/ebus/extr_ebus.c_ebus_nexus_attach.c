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
struct ebus_softc {int sc_nrange; int /*<<< orphan*/  sc_range; int /*<<< orphan*/  sc_ign; } ;
struct ebus_nexus_ranges {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getprop_alloc_multi (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 struct ebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ebus_attach (int /*<<< orphan*/ ,struct ebus_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ebus_nexus_attach(device_t dev)
{
	struct ebus_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

#ifndef SUN4V
	if (OF_getprop(node, "portid", &sc->sc_ign,
	    sizeof(sc->sc_ign)) == -1) {
		device_printf(dev, "could not determine IGN");
		return (ENXIO);
	}
#endif

	sc->sc_nrange = OF_getprop_alloc_multi(node, "ranges",
	    sizeof(struct ebus_nexus_ranges), &sc->sc_range);
	if (sc->sc_nrange == -1) {
		device_printf(dev, "could not get ranges property\n");
		return (ENXIO);
	}
	return (ebus_attach(dev, sc, node));
}