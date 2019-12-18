#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ phandle_t ;
struct TYPE_20__ {int ports_mask; int /*<<< orphan*/  kproc; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  dev; int /*<<< orphan*/  node; int /*<<< orphan*/  sx; int /*<<< orphan*/  sw_addr; } ;
typedef  TYPE_1__ e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_21__ {int /*<<< orphan*/  es_nports; } ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  E6000SW_UNLOCK (TYPE_1__*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  MV88E6141 ; 
 int /*<<< orphan*/  MV88E6190 ; 
 int /*<<< orphan*/  MV88E6341 ; 
 scalar_t__ MVSWITCH (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MVSWITCH_MULTICHIP (TYPE_1__*) ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  PSC_CONTROL ; 
 int PSC_CONTROL_ALT_SPD ; 
 int PSC_CONTROL_FC_ON ; 
 int PSC_CONTROL_FORCED_DPX ; 
 int PSC_CONTROL_FORCED_EEE ; 
 int PSC_CONTROL_FORCED_FC ; 
 int PSC_CONTROL_FORCED_LINK ; 
 int PSC_CONTROL_FORCED_SPD ; 
 int PSC_CONTROL_FULLDPX ; 
 int PSC_CONTROL_LINK_UP ; 
 int PSC_CONTROL_SPD1000 ; 
 int PSC_CONTROL_SPD2500 ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int /*<<< orphan*/  REG_PORT (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SWITCH_GLOBAL_STATUS ; 
 int SWITCH_GLOBAL_STATUS_IR ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int e6000sw_attach_miibus (TYPE_1__*,int) ; 
 int /*<<< orphan*/  e6000sw_detach (int /*<<< orphan*/ ) ; 
 int e6000sw_init_interface (TYPE_1__*,int) ; 
 scalar_t__ e6000sw_is_fixed25port (TYPE_1__*,int) ; 
 scalar_t__ e6000sw_is_fixedport (TYPE_1__*,int) ; 
 int /*<<< orphan*/  e6000sw_is_phyport (TYPE_1__*,int) ; 
 int e6000sw_parse_child_fdt (TYPE_1__*,scalar_t__,int*) ; 
 int e6000sw_readreg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_serdes_power (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  e6000sw_set_vlan_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_setup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  e6000sw_tick ; 
 int /*<<< orphan*/  e6000sw_writereg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ etherswitch_info ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_find_child (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
e6000sw_attach(device_t dev)
{
	bool sgmii;
	e6000sw_softc_t *sc;
	phandle_t child, ports;
	int err, port;
	uint32_t reg;

	err = 0;
	sc = device_get_softc(dev);

	/*
	 * According to the Linux source code, all of the Switch IDs we support
	 * are multi_chip capable, and should go into multi-chip mode if the
	 * sw_addr != 0.
	 */
	if (MVSWITCH_MULTICHIP(sc))
		device_printf(dev, "multi-chip addressing mode (%#x)\n",
		    sc->sw_addr);
	else
		device_printf(dev, "single-chip addressing mode\n");

	sx_init(&sc->sx, "e6000sw");

	E6000SW_LOCK(sc);
	e6000sw_setup(dev, sc);

	ports = ofw_bus_find_child(sc->node, "ports");

	if (ports == 0) {
		device_printf(dev, "failed to parse DTS: no ports found for "
		    "switch\n");
		return (ENXIO);
	}

	for (child = OF_child(ports); child != 0; child = OF_peer(child)) {
		err = e6000sw_parse_child_fdt(sc, child, &port);
		if (err != 0) {
			device_printf(sc->dev, "failed to parse DTS\n");
			goto out_fail;
		}

		/* Port is in use. */
		sc->ports_mask |= (1 << port);

		err = e6000sw_init_interface(sc, port);
		if (err != 0) {
			device_printf(sc->dev, "failed to init interface\n");
			goto out_fail;
		}

		if (e6000sw_is_fixedport(sc, port)) {
			/* Link must be down to change speed force value. */
			reg = e6000sw_readreg(sc, REG_PORT(sc, port),
			    PSC_CONTROL);
			reg &= ~PSC_CONTROL_LINK_UP;
			reg |= PSC_CONTROL_FORCED_LINK;
			e6000sw_writereg(sc, REG_PORT(sc, port), PSC_CONTROL,
			    reg);

			/*
			 * Force speed, full-duplex, EEE off and flow-control
			 * on.
			 */
			reg &= ~(PSC_CONTROL_SPD2500 | PSC_CONTROL_ALT_SPD |
			    PSC_CONTROL_FORCED_FC | PSC_CONTROL_FC_ON |
			    PSC_CONTROL_FORCED_EEE);
			if (e6000sw_is_fixed25port(sc, port))
				reg |= PSC_CONTROL_SPD2500;
			else
				reg |= PSC_CONTROL_SPD1000;
			if (MVSWITCH(sc, MV88E6190) &&
			    e6000sw_is_fixed25port(sc, port))
				reg |= PSC_CONTROL_ALT_SPD;
			reg |= PSC_CONTROL_FORCED_DPX | PSC_CONTROL_FULLDPX |
			    PSC_CONTROL_FORCED_LINK | PSC_CONTROL_LINK_UP |
			    PSC_CONTROL_FORCED_SPD;
			if (!MVSWITCH(sc, MV88E6190))
				reg |= PSC_CONTROL_FORCED_FC | PSC_CONTROL_FC_ON;
			if (MVSWITCH(sc, MV88E6141) ||
			    MVSWITCH(sc, MV88E6341) ||
			    MVSWITCH(sc, MV88E6190))
				reg |= PSC_CONTROL_FORCED_EEE;
			e6000sw_writereg(sc, REG_PORT(sc, port), PSC_CONTROL,
			    reg);
			/* Power on the SERDES interfaces. */
			if (MVSWITCH(sc, MV88E6190) &&
			    (port == 9 || port == 10)) {
				if (e6000sw_is_fixed25port(sc, port))
					sgmii = false;
				else
					sgmii = true;
				e6000sw_serdes_power(sc->dev, port, sgmii);
			}
		}

		/* Don't attach miibus at CPU/fixed ports */
		if (!e6000sw_is_phyport(sc, port))
			continue;

		err = e6000sw_attach_miibus(sc, port);
		if (err != 0) {
			device_printf(sc->dev, "failed to attach miibus\n");
			goto out_fail;
		}
	}

	etherswitch_info.es_nports = sc->num_ports;

	/* Default to port vlan. */
	e6000sw_set_vlan_mode(sc, ETHERSWITCH_VLAN_PORT);

	reg = e6000sw_readreg(sc, REG_GLOBAL, SWITCH_GLOBAL_STATUS);
	if (reg & SWITCH_GLOBAL_STATUS_IR)
		device_printf(dev, "switch is ready.\n");
	E6000SW_UNLOCK(sc);

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	kproc_create(e6000sw_tick, sc, &sc->kproc, 0, 0, "e6000sw tick kproc");

	return (0);

out_fail:
	E6000SW_UNLOCK(sc);
	e6000sw_detach(dev);

	return (err);
}