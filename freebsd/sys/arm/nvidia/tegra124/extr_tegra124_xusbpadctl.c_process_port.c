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
struct padctl_softc {int /*<<< orphan*/  dev; } ;
struct padctl_port {int type; int internal; int enabled; int /*<<< orphan*/ * lane; int /*<<< orphan*/  idx; int /*<<< orphan*/  supply_vbus; int /*<<< orphan*/  companion; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  PADCTL_PAD_HSIC ; 
 int /*<<< orphan*/  PADCTL_PAD_ULPI ; 
 int /*<<< orphan*/  PADCTL_PAD_USB2 ; 
#define  PADCTL_PORT_HSIC 131 
#define  PADCTL_PORT_ULPI 130 
#define  PADCTL_PORT_USB2 129 
#define  PADCTL_PORT_USB3 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* search_pad_lane (struct padctl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct padctl_port* search_port (struct padctl_softc*,char*) ; 
 int /*<<< orphan*/ * search_usb3_pad_lane (struct padctl_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
process_port(struct padctl_softc *sc, phandle_t node)
{

	struct padctl_port *port;
	char *name;
	int rv;

	name = NULL;
	rv = OF_getprop_alloc(node, "name", (void **)&name);
	if (rv <= 0) {
		device_printf(sc->dev, "Cannot read port name.\n");
		return (ENXIO);
	}

	port = search_port(sc, name);
	if (port == NULL) {
		device_printf(sc->dev, "Unknown port: %s\n", name);
		rv = ENXIO;
		goto end;
	}

	if (port->type == PADCTL_PORT_USB3) {
		rv = OF_getencprop(node,  "nvidia,usb2-companion",
		   &(port->companion), sizeof(port->companion));
		if (rv <= 0) {
			device_printf(sc->dev,
			    "Missing 'nvidia,usb2-companion' property "
			    "for port: %s\n", name);
			rv = ENXIO;
			goto end;
		}
	}

	if (OF_hasprop(node, "vbus-supply")) {
		rv = regulator_get_by_ofw_property(sc->dev, 0,
		    "vbus-supply", &port->supply_vbus);
		if (rv <= 0) {
			device_printf(sc->dev,
			    "Cannot get 'vbus-supply' regulator "
			    "for port: %s\n", name);
			rv = ENXIO;
			goto end;
		}
	}

	if (OF_hasprop(node, "nvidia,internal"))
		port->internal = true;
	/* Find assigned lane */
	if (port->lane == NULL) {
		switch(port->type) {
		/* Routing is fixed for USB2, ULPI AND HSIC. */
		case PADCTL_PORT_USB2:
			port->lane = search_pad_lane(sc, PADCTL_PAD_USB2,
			    port->idx);
			break;
		case PADCTL_PORT_ULPI:
			port->lane = search_pad_lane(sc, PADCTL_PAD_ULPI,
			    port->idx);
			break;
		case PADCTL_PORT_HSIC:
			port->lane = search_pad_lane(sc, PADCTL_PAD_HSIC,
			    port->idx);
			break;
		case PADCTL_PORT_USB3:
			port->lane = search_usb3_pad_lane(sc, port->idx);
			break;
		}
	}
	if (port->lane == NULL) {
		device_printf(sc->dev, "Cannot find lane for port: %s\n", name);
		rv = ENXIO;
		goto end;
	}
	port->enabled = true;
	rv = 0;
end:
	if (name != NULL)
		OF_prop_free(name);
	return (rv);
}