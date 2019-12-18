#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ phandle_t ;
struct TYPE_7__ {int swid; int sw_addr; int phy_base; int num_ports; int /*<<< orphan*/  sx; scalar_t__ node; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int /*<<< orphan*/  E6000SW_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  E6000SW_UNLOCK (TYPE_1__*) ; 
 int ENXIO ; 
#define  MV88E6141 133 
#define  MV88E6172 132 
#define  MV88E6176 131 
#define  MV88E6190 130 
#define  MV88E6341 129 
#define  MV88E6352 128 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 int /*<<< orphan*/  REG_PORT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ID ; 
 scalar_t__ bootverbose ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int e6000sw_readreg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_find_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
e6000sw_probe(device_t dev)
{
	e6000sw_softc_t *sc;
	const char *description;
	phandle_t switch_node;

	sc = device_get_softc(dev);
	switch_node = ofw_bus_find_compatible(OF_finddevice("/"),
	    "marvell,mv88e6085");
	if (switch_node == 0) {
		switch_node = ofw_bus_find_compatible(OF_finddevice("/"),
		    "marvell,mv88e6190");

		if (switch_node == 0)
			return (ENXIO);

		/*
		 * Trust DTS and fix the port register offset for the MV88E6190
		 * detection bellow.
		 */
		sc->swid = MV88E6190;
	}

	if (bootverbose)
		device_printf(dev, "Found switch_node: 0x%x\n", switch_node);

	sc->dev = dev;
	sc->node = switch_node;

	if (OF_getencprop(sc->node, "reg", &sc->sw_addr,
	    sizeof(sc->sw_addr)) < 0)
		return (ENXIO);
	if (sc->sw_addr < 0 || sc->sw_addr > 32)
		return (ENXIO);

	/*
	 * Create temporary lock, just to satisfy assertions,
	 * when obtaining the switch ID. Destroy immediately afterwards.
	 */
	sx_init(&sc->sx, "e6000sw_tmp");
	E6000SW_LOCK(sc);
	sc->swid = e6000sw_readreg(sc, REG_PORT(sc, 0), SWITCH_ID) & 0xfff0;
	E6000SW_UNLOCK(sc);
	sx_destroy(&sc->sx);

	switch (sc->swid) {
	case MV88E6141:
		description = "Marvell 88E6141";
		sc->phy_base = 0x10;
		sc->num_ports = 6;
		break;
	case MV88E6341:
		description = "Marvell 88E6341";
		sc->phy_base = 0x10;
		sc->num_ports = 6;
		break;
	case MV88E6352:
		description = "Marvell 88E6352";
		sc->num_ports = 7;
		break;
	case MV88E6172:
		description = "Marvell 88E6172";
		sc->num_ports = 7;
		break;
	case MV88E6176:
		description = "Marvell 88E6176";
		sc->num_ports = 7;
		break;
	case MV88E6190:
		description = "Marvell 88E6190";
		sc->num_ports = 11;
		break;
	default:
		device_printf(dev, "Unrecognized device, id 0x%x.\n", sc->swid);
		return (ENXIO);
	}

	device_set_desc(dev, description);

	return (BUS_PROBE_DEFAULT);
}