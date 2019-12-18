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
struct omap_uhh_softc {int /*<<< orphan*/ * port_mode; int /*<<< orphan*/  uhh_mem_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  propname ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_HCD_OMAP_MODE_HSIC ; 
 int /*<<< orphan*/  EHCI_HCD_OMAP_MODE_PHY ; 
 int /*<<< orphan*/  EHCI_HCD_OMAP_MODE_TLL ; 
 int /*<<< orphan*/  EHCI_HCD_OMAP_MODE_UNKNOWN ; 
 int ENXIO ; 
 int OF_child (int) ; 
 scalar_t__ OF_getprop_alloc (int,char*,void**) ; 
 int OF_peer (int) ; 
 int OMAP_HS_USB_PORTS ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 struct omap_uhh_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_uhh_detach (int /*<<< orphan*/ ) ; 
 int omap_uhh_init (struct omap_uhh_softc*) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
omap_uhh_attach(device_t dev)
{
	struct omap_uhh_softc *isc = device_get_softc(dev);
	int err;
	int rid;
	int i;
	phandle_t node;
	char propname[16];
	char *mode;

	/* save the device */
	isc->sc_dev = dev;

	/* Allocate resource for the UHH register set */
	rid = 0;
	isc->uhh_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (!isc->uhh_mem_res) {
		device_printf(dev, "Error: Could not map UHH memory\n");
		goto error;
	}

	node = ofw_bus_get_node(dev);

	if (node == -1)
		goto error;

	/* Get port modes from FDT */
	for (i = 0; i < OMAP_HS_USB_PORTS; i++) {
		isc->port_mode[i] = EHCI_HCD_OMAP_MODE_UNKNOWN;
		snprintf(propname, sizeof(propname),
		    "port%d-mode", i+1);

		if (OF_getprop_alloc(node, propname, (void**)&mode) <= 0)
			continue;
		if (strcmp(mode, "ehci-phy") == 0)
			isc->port_mode[i] = EHCI_HCD_OMAP_MODE_PHY;
		else if (strcmp(mode, "ehci-tll") == 0)
			isc->port_mode[i] = EHCI_HCD_OMAP_MODE_TLL;
		else if (strcmp(mode, "ehci-hsic") == 0)
			isc->port_mode[i] = EHCI_HCD_OMAP_MODE_HSIC;
	}

	/* Initialise the ECHI registers */
	err = omap_uhh_init(isc);
	if (err) {
		device_printf(dev, "Error: could not setup OMAP EHCI, %d\n", err);
		goto error;
	}

	simplebus_init(dev, node);

	/*
	 * Allow devices to identify.
	 */
	bus_generic_probe(dev);

	/*
	 * Now walk the OFW tree and attach top-level devices.
	 */
	for (node = OF_child(node); node > 0; node = OF_peer(node))
		simplebus_add_device(dev, node, 0, NULL, -1, NULL);
	return (bus_generic_attach(dev));

error:
	omap_uhh_detach(dev);
	return (ENXIO);
}