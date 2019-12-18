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
struct rk_typec_phy_softc {int phy_ctrl_id; int /*<<< orphan*/  res; int /*<<< orphan*/  rst_tcphy; int /*<<< orphan*/  rst_pipe; int /*<<< orphan*/  rst_uphy; int /*<<< orphan*/  tcpdphy_ref; int /*<<< orphan*/  tcpdcore; int /*<<< orphan*/  grf; int /*<<< orphan*/  dev; } ;
struct phynode_init_def {int ofw_node; int /*<<< orphan*/  id; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  reg_prop ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (int,char*,int*,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int) ; 
 int /*<<< orphan*/  RK3399_TYPEC_PHY_USB3 ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_set_assigned (int /*<<< orphan*/ ,int) ; 
 struct rk_typec_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hwreset_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int ofw_bus_find_child (int,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_node_status_okay (int) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 
 int /*<<< orphan*/  rk_typec_phy_phynode_class ; 
 int /*<<< orphan*/  rk_typec_phy_spec ; 
 scalar_t__ syscon_get_by_ofw_property (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rk_typec_phy_attach(device_t dev)
{
	struct rk_typec_phy_softc *sc;
	struct phynode_init_def phy_init;
	struct phynode *phynode;
	phandle_t node, usb3;
	phandle_t reg_prop[4];

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* 
	 * Find out which phy we are.
	 * There is not property for this so we need to know the
	 * address to use the correct GRF registers.
	 */
	if (OF_getencprop(node, "reg", reg_prop, sizeof(reg_prop)) <= 0) {
		device_printf(dev, "Cannot guess phy controller id\n");
		return (ENXIO);
	}
	switch (reg_prop[1]) {
	case 0xff7c0000:
		sc->phy_ctrl_id = 0;
		break;
	case 0xff800000:
		sc->phy_ctrl_id = 1;
		break;
	default:
		device_printf(dev, "Unknown address %x for typec-phy\n", reg_prop[1]);
		return (ENXIO);
	}

	if (bus_alloc_resources(dev, rk_typec_phy_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		goto fail;
	}

	if (syscon_get_by_ofw_property(dev, node,
	    "rockchip,grf", &sc->grf) != 0) {
		device_printf(dev, "Cannot get syscon handle\n");
		goto fail;
	}

	if (clk_get_by_ofw_name(dev, 0, "tcpdcore", &sc->tcpdcore) != 0) {
		device_printf(dev, "Cannot get tcpdcore clock\n");
		goto fail;
	}
	if (clk_get_by_ofw_name(dev, 0, "tcpdphy-ref", &sc->tcpdphy_ref) != 0) {
		device_printf(dev, "Cannot get tcpdphy-ref clock\n");
		goto fail;
	}

	if (hwreset_get_by_ofw_name(dev, 0, "uphy", &sc->rst_uphy) != 0) {
		device_printf(dev, "Cannot get uphy reset\n");
		goto fail;
	}
	if (hwreset_get_by_ofw_name(dev, 0, "uphy-pipe", &sc->rst_pipe) != 0) {
		device_printf(dev, "Cannot get uphy-pipe reset\n");
		goto fail;
	}
	if (hwreset_get_by_ofw_name(dev, 0, "uphy-tcphy", &sc->rst_tcphy) != 0) {
		device_printf(dev, "Cannot get uphy-tcphy reset\n");
		goto fail;
	}

	/* 
	 * Make sure that the module is asserted 
	 * We need to deassert in a certain order when we enable the phy
	 */
	hwreset_assert(sc->rst_uphy);
	hwreset_assert(sc->rst_pipe);
	hwreset_assert(sc->rst_tcphy);

	/* Set the assigned clocks parent and freq */
	if (clk_set_assigned(dev, node) != 0) {
		device_printf(dev, "clk_set_assigned failed\n");
		goto fail;
	}

	/* Only usb3 port is supported right now */
	usb3 = ofw_bus_find_child(node, "usb3-port");
	if (usb3 == 0) {
		device_printf(dev, "Cannot find usb3-port child node\n");
		goto fail;
	}
	/* If the child isn't enable attach the driver
	 *  but do not register the PHY. 
	 */
	if (!ofw_bus_node_status_okay(usb3))
		return (0);

	phy_init.id = RK3399_TYPEC_PHY_USB3;
	phy_init.ofw_node = usb3;
	phynode = phynode_create(dev, &rk_typec_phy_phynode_class, &phy_init);
	if (phynode == NULL) {
		device_printf(dev, "failed to create phy usb3-port\n");
		goto fail;
	}
	if (phynode_register(phynode) == NULL) {
		device_printf(dev, "failed to register phy usb3-port\n");
		goto fail;
	}

	OF_device_register_xref(OF_xref_from_node(usb3), dev);

	return (0);

fail:
	bus_release_resources(dev, rk_typec_phy_spec, &sc->res);

	return (ENXIO);
}