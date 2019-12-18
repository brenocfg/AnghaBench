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
typedef  scalar_t__ uint32_t ;
struct ip17x_softc {int miipoll; int /*<<< orphan*/  sc_switchtype; } ;
typedef  scalar_t__ phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int IP175D_ID_PHY ; 
 int /*<<< orphan*/  IP175D_ID_REG ; 
#define  IP17X_IP175A 129 
#define  IP17X_IP175C 128 
 scalar_t__ IP17X_OUI ; 
 int /*<<< orphan*/  IP17X_SWITCH_IP175A ; 
 int /*<<< orphan*/  IP17X_SWITCH_IP175C ; 
 int /*<<< orphan*/  IP17X_SWITCH_IP175D ; 
 int /*<<< orphan*/  IP17X_SWITCH_IP178C ; 
 scalar_t__ MDIO_READREG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ MII_MODEL (scalar_t__) ; 
 scalar_t__ MII_OUI (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MII_PHYIDR1 ; 
 int /*<<< orphan*/  MII_PHYIDR2 ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fdt_find_compatible (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
ip17x_probe(device_t dev)
{
	struct ip17x_softc *sc;
	uint32_t oui, model, phy_id1, phy_id2;
#ifdef FDT
	phandle_t ip17x_node;
	pcell_t cell;

	ip17x_node = fdt_find_compatible(OF_finddevice("/"),
	    "icplus,ip17x", 0);

	if (ip17x_node == 0)
		return (ENXIO);
#endif

	sc = device_get_softc(dev);

	/* Read ID from PHY 0. */
	phy_id1 = MDIO_READREG(device_get_parent(dev), 0, MII_PHYIDR1);
	phy_id2 = MDIO_READREG(device_get_parent(dev), 0, MII_PHYIDR2);

	oui = MII_OUI(phy_id1, phy_id2);
	model = MII_MODEL(phy_id2);
	/* We only care about IC+ devices. */
	if (oui != IP17X_OUI) {
		device_printf(dev,
		    "Unsupported IC+ switch. Unknown OUI: %#x\n", oui);
		return (ENXIO);
	}

	switch (model) {
	case IP17X_IP175A:
		sc->sc_switchtype = IP17X_SWITCH_IP175A;
		break;
	case IP17X_IP175C:
		sc->sc_switchtype = IP17X_SWITCH_IP175C;
		break;
	default:
		device_printf(dev, "Unsupported IC+ switch model: %#x\n",
		    model);
		return (ENXIO);
	}

	/* IP175D has a specific ID register. */
	model = MDIO_READREG(device_get_parent(dev), IP175D_ID_PHY,
	    IP175D_ID_REG);
	if (model == 0x175d)
		sc->sc_switchtype = IP17X_SWITCH_IP175D;
	else {
		/* IP178 has more PHYs.  Try it. */
		model = MDIO_READREG(device_get_parent(dev), 5, MII_PHYIDR1);
		if (phy_id1 == model)
			sc->sc_switchtype = IP17X_SWITCH_IP178C;
	}

	sc->miipoll = 1;
#ifdef FDT
	if ((OF_getencprop(ip17x_node, "mii-poll",
	    &cell, sizeof(cell))) > 0)
		sc->miipoll = cell ? 1 : 0;
#else
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "mii-poll", &sc->miipoll);
#endif
	device_set_desc_copy(dev, "IC+ IP17x switch driver");
	return (BUS_PROBE_DEFAULT);
}