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
struct rk_usb2phy_softc {int /*<<< orphan*/  phy_supply; int /*<<< orphan*/  clk; int /*<<< orphan*/  grf; int /*<<< orphan*/  dev; } ;
struct phynode_init_def {scalar_t__ ofw_node; int /*<<< orphan*/  id; } ;
struct phynode {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 int /*<<< orphan*/  RK3399_USBPHY_HOST ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 struct rk_usb2phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_node_status_okay (scalar_t__) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 
 int /*<<< orphan*/  regulator_get_by_ofw_property (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int rk_usb2phy_export_clock (struct rk_usb2phy_softc*) ; 
 int /*<<< orphan*/  rk_usb2phy_phynode_class ; 
 scalar_t__ syscon_get_handle_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rk_usb2phy_attach(device_t dev)
{
	struct rk_usb2phy_softc *sc;
	struct phynode_init_def phy_init;
	struct phynode *phynode;
	phandle_t node, host;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	if (syscon_get_handle_default(dev, &sc->grf) != 0) {
		device_printf(dev, "Cannot get syscon handle\n");
		return (ENXIO);
	}

	if (clk_get_by_ofw_name(dev, 0, "phyclk", &sc->clk) != 0) {
		device_printf(dev, "Cannot get clock\n");
		return (ENXIO);
	}
	err = clk_enable(sc->clk);
	if (err != 0) {
		device_printf(dev, "Could not enable clock %s\n",
		    clk_get_name(sc->clk));
		return (ENXIO);
	}

	err = rk_usb2phy_export_clock(sc);
	if (err != 0)
		return (err);

	/* Only host is supported right now */

	host = ofw_bus_find_child(node, "host-port");
	if (host == 0) {
		device_printf(dev, "Cannot find host-port child node\n");
		return (ENXIO);
	}

	if (!ofw_bus_node_status_okay(host)) {
		device_printf(dev, "host-port isn't okay\n");
		return (0);
	}

	regulator_get_by_ofw_property(dev, host, "phy-supply", &sc->phy_supply);
	phy_init.id = RK3399_USBPHY_HOST;
	phy_init.ofw_node = host;
	phynode = phynode_create(dev, &rk_usb2phy_phynode_class, &phy_init);
	if (phynode == NULL) {
		device_printf(dev, "failed to create host USB2PHY\n");
		return (ENXIO);
	}
	if (phynode_register(phynode) == NULL) {
		device_printf(dev, "failed to register host USB2PHY\n");
		return (ENXIO);
	}

	OF_device_register_xref(OF_xref_from_node(host), dev);

	return (0);
}