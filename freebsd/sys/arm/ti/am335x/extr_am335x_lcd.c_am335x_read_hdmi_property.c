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
typedef  int /*<<< orphan*/  xref ;
struct am335x_lcd_softc {scalar_t__ sc_hdmi_framer; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  hdmi_xref ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 scalar_t__ OF_node_from_xref (scalar_t__) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ OF_xref_from_node (scalar_t__) ; 
 struct am335x_lcd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
am335x_read_hdmi_property(device_t dev)
{
	phandle_t node, xref;
	phandle_t endpoint;
	phandle_t hdmi_xref;
	struct am335x_lcd_softc *sc;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);
	sc->sc_hdmi_framer = 0;

	/*
	 * Old FreeBSD way of referencing to HDMI framer
	 */
	if (OF_getencprop(node, "hdmi", &hdmi_xref, sizeof(hdmi_xref)) != -1) {
		sc->sc_hdmi_framer = hdmi_xref;
		return;
	}

	/*
	 * Use bindings described in Linux docs:
	 * bindings/media/video-interfaces.txt
	 * We assume that the only endpoint in LCDC node
	 * is HDMI framer.
	 */
	node = ofw_bus_find_child(node, "port");

	/* No media bindings */
	if (node == 0)
		return;

	for (endpoint = OF_child(node); endpoint != 0; endpoint = OF_peer(endpoint)) {
		if (OF_getencprop(endpoint, "remote-endpoint", &xref, sizeof(xref)) != -1) {
			/* port/port@0/endpoint@0 */
			node = OF_node_from_xref(xref);
			/* port/port@0 */
			node = OF_parent(node);
			/* port */
			node = OF_parent(node);
			/* actual owner of port, in our case HDMI framer */
			sc->sc_hdmi_framer = OF_xref_from_node(OF_parent(node));
			if (sc->sc_hdmi_framer != 0)
				return;
		}
	}
}