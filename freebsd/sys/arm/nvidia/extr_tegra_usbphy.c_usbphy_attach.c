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
struct usbphy_softc {int have_utmi_regs; scalar_t__ dr_mode; scalar_t__ ifc_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  supply_vbus; int /*<<< orphan*/  clk_reg; int /*<<< orphan*/  clk_pllu; int /*<<< orphan*/  reset_usb; int /*<<< orphan*/  clk_pads; int /*<<< orphan*/  reset_pads; int /*<<< orphan*/ * mem_res; void* pads_res; } ;
struct phynode_init_def {int id; int /*<<< orphan*/  ofw_node; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  phy_init ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ USB_DR_MODE_HOST ; 
 scalar_t__ USB_DR_MODE_UNKNOWN ; 
 scalar_t__ USB_IFC_TYPE_UTMI ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bzero (struct phynode_init_def*,int) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct usbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_get_dr_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ usb_get_ifc_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usbphy_phynode_class ; 
 int usbphy_utmi_read_params (struct usbphy_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usbphy_attach(device_t dev)
{
	struct usbphy_softc *sc;
	int rid, rv;
	phandle_t node;
	struct phynode *phynode;
	struct phynode_init_def phy_init;

	sc = device_get_softc(dev);
	sc->dev = dev;

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		return (ENXIO);
	}

	rid = 1;
	sc->pads_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);

	rv = hwreset_get_by_ofw_name(sc->dev, 0, "usb", &sc->reset_usb);
	if (rv != 0) {
		device_printf(dev, "Cannot get 'usb' reset\n");
		return (ENXIO);
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "utmi-pads", &sc->reset_pads);
	if (rv != 0) {
		device_printf(dev, "Cannot get 'utmi-pads' reset\n");
		return (ENXIO);
	}

	rv = clk_get_by_ofw_name(sc->dev, 0, "reg", &sc->clk_reg);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'reg' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "pll_u", &sc->clk_pllu);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pll_u' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "utmi-pads", &sc->clk_pads);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'utmi-pads' clock\n");
		return (ENXIO);
	}

	rv = hwreset_deassert(sc->reset_usb);
	if (rv != 0) {
		device_printf(dev, "Cannot unreset 'usb' reset\n");
		return (ENXIO);
	}

	rv = clk_enable(sc->clk_pllu);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'pllu' clock\n");
		return (ENXIO);
	}
	rv = clk_enable(sc->clk_reg);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'reg' clock\n");
		return (ENXIO);
	}
	if (OF_hasprop(node, "nvidia,has-utmi-pad-registers"))
		sc->have_utmi_regs = true;

	sc->dr_mode = usb_get_dr_mode(dev, node, "dr_mode");
	if (sc->dr_mode == USB_DR_MODE_UNKNOWN)
		sc->dr_mode = USB_DR_MODE_HOST;

	sc->ifc_type = usb_get_ifc_mode(dev, node, "phy_type");

	/* We supports only utmi phy mode for now .... */
	if (sc->ifc_type != USB_IFC_TYPE_UTMI) {
		device_printf(dev, "Unsupported phy type\n");
		return (ENXIO);
	}
	rv = usbphy_utmi_read_params(sc, node);
	if (rv < 0)
		return rv;

	if (OF_hasprop(node, "vbus-supply")) {
		rv = regulator_get_by_ofw_property(sc->dev, 0, "vbus-supply",
		    &sc->supply_vbus);
		if (rv != 0) {
			device_printf(sc->dev,
			   "Cannot get \"vbus\" regulator\n");
			return (ENXIO);
		}
		rv = regulator_enable(sc->supply_vbus);
		if (rv != 0) {
			device_printf(sc->dev,
			    "Cannot enable  \"vbus\" regulator\n");
			return (rv);
		}
	}

	/* Create and register phy. */
	bzero(&phy_init, sizeof(phy_init));
	phy_init.id = 1;
	phy_init.ofw_node = node;
	phynode = phynode_create(dev, &usbphy_phynode_class, &phy_init);
	if (phynode == NULL) {
		device_printf(sc->dev, "Cannot create phy\n");
		return (ENXIO);
	}
	if (phynode_register(phynode) == NULL) {
		device_printf(sc->dev, "Cannot create phy\n");
		return (ENXIO);
	}

	return (0);
}