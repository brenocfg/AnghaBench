#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* ip17x_set_vlan_mode ) (struct ip17x_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ip17x_reset ) (struct ip17x_softc*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  es_nvlangroups; int /*<<< orphan*/  es_name; } ;
struct ip17x_softc {int phymask; int media; int cpuport; int numports; int /*<<< orphan*/  callout_tick; scalar_t__ miipoll; TYPE_2__ hal; void* portphy; void* miibus; void* pvid; void* ifp; TYPE_1__ info; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  IP175C ; 
 int /*<<< orphan*/  IP175D ; 
 scalar_t__ IP17X_IS_SWITCH (struct ip17x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP17X_MAX_VLANS ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_IP17X ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip175c_attach (struct ip17x_softc*) ; 
 int /*<<< orphan*/  ip175d_attach (struct ip17x_softc*) ; 
 int ip17x_attach_phys (struct ip17x_softc*) ; 
 int /*<<< orphan*/  ip17x_tick (struct ip17x_softc*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ip17x_softc*) ; 
 int /*<<< orphan*/  stub2 (struct ip17x_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip17x_attach(device_t dev)
{
	struct ip17x_softc *sc;
	int err;

	sc = device_get_softc(dev);

	sc->sc_dev = dev;
	mtx_init(&sc->sc_mtx, "ip17x", NULL, MTX_DEF);
	strlcpy(sc->info.es_name, device_get_desc(dev),
	    sizeof(sc->info.es_name));

	/* XXX Defaults */
	sc->phymask = 0x0f;
	sc->media = 100;

	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "phymask", &sc->phymask);

	/* Number of vlans supported by the switch. */
	sc->info.es_nvlangroups = IP17X_MAX_VLANS;

	/* Attach the switch related functions. */
	if (IP17X_IS_SWITCH(sc, IP175C))
		ip175c_attach(sc);
	else if (IP17X_IS_SWITCH(sc, IP175D))
		ip175d_attach(sc);
	else
		/* We don't have support to all the models yet :-/ */
		return (ENXIO);

	/* Always attach the cpu port. */
	sc->phymask |= (1 << sc->cpuport);

	sc->ifp = malloc(sizeof(struct ifnet *) * sc->numports, M_IP17X,
	    M_WAITOK | M_ZERO);
	sc->pvid = malloc(sizeof(uint32_t) * sc->numports, M_IP17X,
	    M_WAITOK | M_ZERO);
	sc->miibus = malloc(sizeof(device_t *) * sc->numports, M_IP17X,
	    M_WAITOK | M_ZERO);
	sc->portphy = malloc(sizeof(int) * sc->numports, M_IP17X,
	    M_WAITOK | M_ZERO);

	/* Initialize the switch. */
	sc->hal.ip17x_reset(sc);

	/*
	 * Attach the PHYs and complete the bus enumeration.
	 */
	err = ip17x_attach_phys(sc);
	if (err != 0)
		return (err);

	/*
	 * Set the switch to port based vlans or disabled (if not supported
	 * on this model).
	 */
	sc->hal.ip17x_set_vlan_mode(sc, ETHERSWITCH_VLAN_PORT);

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	err = bus_generic_attach(dev);
	if (err != 0)
		return (err);
	
	if (sc->miipoll) {
		callout_init(&sc->callout_tick, 0);

		ip17x_tick(sc);
	}
	
	return (0);
}