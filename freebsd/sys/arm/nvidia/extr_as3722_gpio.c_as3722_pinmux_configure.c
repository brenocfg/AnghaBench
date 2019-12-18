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
struct as3722_softc {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_node_from_xref (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int as3722_pinmux_process_node (struct as3722_softc*,scalar_t__) ; 
 struct as3722_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_node_status_okay (scalar_t__) ; 

int as3722_pinmux_configure(device_t dev, phandle_t cfgxref)
{
	struct as3722_softc *sc;
	phandle_t node, cfgnode;
	int rv;

	sc = device_get_softc(dev);
	cfgnode = OF_node_from_xref(cfgxref);

	for (node = OF_child(cfgnode); node != 0; node = OF_peer(node)) {
		if (!ofw_bus_node_status_okay(node))
			continue;
		rv = as3722_pinmux_process_node(sc, node);
		if (rv != 0)
			device_printf(dev, "Failed to process pinmux");

	}
	return (0);
}