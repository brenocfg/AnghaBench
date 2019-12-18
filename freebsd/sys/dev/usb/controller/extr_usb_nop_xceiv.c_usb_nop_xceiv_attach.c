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
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_nop_xceiv_softc {scalar_t__ clk_freq; int /*<<< orphan*/  vcc_supply; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;
struct phynode_init_def {int /*<<< orphan*/  ofw_node; scalar_t__ id; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct usb_nop_xceiv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 
 int /*<<< orphan*/  regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_nop_xceiv_phynode_class ; 

__attribute__((used)) static int
usb_nop_xceiv_attach(device_t dev)
{
	struct usb_nop_xceiv_softc *sc;
	struct phynode *phynode;
	struct phynode_init_def phy_init;
	phandle_t node;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* Parse the optional properties */
	OF_getencprop(node, "clock-frequency", &sc->clk_freq, sizeof(uint32_t));

	error = clk_get_by_ofw_name(dev, node, "main_clk", &sc->clk);
	if (error != 0 && sc->clk_freq != 0) {
		device_printf(dev, "clock property is mandatory if clock-frequency is present\n");
		return (ENXIO);
	}

	regulator_get_by_ofw_property(dev, node, "vcc-supply", &sc->vcc_supply);

	phy_init.id = 0;
	phy_init.ofw_node = node;
	phynode = phynode_create(dev, &usb_nop_xceiv_phynode_class,
	    &phy_init);
	if (phynode == NULL) {
		device_printf(dev, "failed to create USB NOP PHY\n");
		return (ENXIO);
	}
	if (phynode_register(phynode) == NULL) {
		device_printf(dev, "failed to create USB NOP PHY\n");
		return (ENXIO);
	}

	OF_device_register_xref(OF_xref_from_node(node), dev);

	return (0);
}