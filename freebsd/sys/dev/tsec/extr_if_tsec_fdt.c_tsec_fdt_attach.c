#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bst; int /*<<< orphan*/  bsh; } ;
struct tsec_softc {int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  receive_lock; int /*<<< orphan*/ * sc_rres; scalar_t__ sc_rrid; int /*<<< orphan*/  sc_transmit_irid; int /*<<< orphan*/  sc_transmit_ihand; int /*<<< orphan*/  sc_transmit_ires; int /*<<< orphan*/  sc_receive_irid; int /*<<< orphan*/  sc_receive_ihand; int /*<<< orphan*/  sc_receive_ires; int /*<<< orphan*/  sc_error_irid; int /*<<< orphan*/  sc_error_ihand; int /*<<< orphan*/  sc_error_ires; TYPE_1__ sc_bas; int /*<<< orphan*/  ic_lock; int /*<<< orphan*/  tsec_callout; int /*<<< orphan*/  phy_regoff; int /*<<< orphan*/  phyaddr; int /*<<< orphan*/  phy_bsh; int /*<<< orphan*/  phy_bst; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  phy ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OF_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_decode_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TSEC_REG_MIIBASE ; 
 int /*<<< orphan*/  TSEC_RID_ERRIRQ ; 
 int /*<<< orphan*/  TSEC_RID_RXIRQ ; 
 int /*<<< orphan*/  TSEC_RID_TXIRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct tsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_list*,int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_reg_to_rl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource_list*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ tsec_attach (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_error_intr ; 
 int /*<<< orphan*/  tsec_receive_intr ; 
 int /*<<< orphan*/  tsec_release_intr (struct tsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int tsec_setup_intr (struct tsec_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tsec_transmit_intr ; 

__attribute__((used)) static int
tsec_fdt_attach(device_t dev)
{
	struct tsec_softc *sc;
	struct resource_list *rl;
	phandle_t child, mdio, phy;
	int acells, scells;
	int error = 0;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->node = ofw_bus_get_node(dev);

	if (fdt_addrsize_cells(sc->node, &acells, &scells) != 0) {
		acells = 1;
		scells = 1;
	}
	if (ofw_bus_is_compatible(dev, "fsl,etsec2")) {
		rl = BUS_GET_RESOURCE_LIST(device_get_parent(dev), dev);

		/*
		 * TODO: Add all children resources to the list.  Will be
		 * required to support multigroup mode.
		 */
		child = OF_child(sc->node);
		ofw_bus_reg_to_rl(dev, child, acells, scells, rl);
		ofw_bus_intr_to_rl(dev, child, rl, NULL);
	}

	/* Get phy address from fdt */
	if (OF_getencprop(sc->node, "phy-handle", &phy, sizeof(phy)) <= 0) {
		device_printf(dev, "PHY not found in device tree");
		return (ENXIO);
	}

	phy = OF_node_from_xref(phy);
	mdio = OF_parent(phy);
	OF_decode_addr(mdio, 0, &sc->phy_bst, &sc->phy_bsh, NULL);
	OF_getencprop(phy, "reg", &sc->phyaddr, sizeof(sc->phyaddr));

	/*
	 * etsec2 MDIO nodes are given the MDIO module base address, so we need
	 * to add the MII offset to get the PHY registers.
	 */
	if (ofw_bus_node_is_compatible(mdio, "fsl,etsec2-mdio"))
		sc->phy_regoff = TSEC_REG_MIIBASE;

	/* Init timer */
	callout_init(&sc->tsec_callout, 1);

	/* Init locks */
	mtx_init(&sc->transmit_lock, device_get_nameunit(dev), "TSEC TX lock",
	    MTX_DEF);
	mtx_init(&sc->receive_lock, device_get_nameunit(dev), "TSEC RX lock",
	    MTX_DEF);
	mtx_init(&sc->ic_lock, device_get_nameunit(dev), "TSEC IC lock",
	    MTX_DEF);

	/* Allocate IO memory for TSEC registers */
	sc->sc_rrid = 0;
	sc->sc_rres = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rrid,
	    RF_ACTIVE);
	if (sc->sc_rres == NULL) {
		device_printf(dev, "could not allocate IO memory range!\n");
		goto fail1;
	}
	sc->sc_bas.bsh = rman_get_bushandle(sc->sc_rres);
	sc->sc_bas.bst = rman_get_bustag(sc->sc_rres);

	/* TSEC attach */
	if (tsec_attach(sc) != 0) {
		device_printf(dev, "could not be configured\n");
		goto fail2;
	}

	/* Set up interrupts (TX/RX/ERR) */
	sc->sc_transmit_irid = TSEC_RID_TXIRQ;
	error = tsec_setup_intr(sc, &sc->sc_transmit_ires,
	    &sc->sc_transmit_ihand, &sc->sc_transmit_irid,
	    tsec_transmit_intr, "TX");
	if (error)
		goto fail2;

	sc->sc_receive_irid = TSEC_RID_RXIRQ;
	error = tsec_setup_intr(sc, &sc->sc_receive_ires,
	    &sc->sc_receive_ihand, &sc->sc_receive_irid,
	    tsec_receive_intr, "RX");
	if (error)
		goto fail3;

	sc->sc_error_irid = TSEC_RID_ERRIRQ;
	error = tsec_setup_intr(sc, &sc->sc_error_ires,
	    &sc->sc_error_ihand, &sc->sc_error_irid,
	    tsec_error_intr, "ERR");
	if (error)
		goto fail4;

	return (0);

fail4:
	tsec_release_intr(sc, sc->sc_receive_ires, sc->sc_receive_ihand,
	    sc->sc_receive_irid, "RX");
fail3:
	tsec_release_intr(sc, sc->sc_transmit_ires, sc->sc_transmit_ihand,
	    sc->sc_transmit_irid, "TX");
fail2:
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rrid, sc->sc_rres);
fail1:
	mtx_destroy(&sc->receive_lock);
	mtx_destroy(&sc->transmit_lock);
	return (ENXIO);
}