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
struct TYPE_2__ {scalar_t__ es_nvlangroups; int /*<<< orphan*/  es_name; } ;
struct ukswitch_softc {int numports; int phymask; int phyoffset; int cpuport; int media; int /*<<< orphan*/  callout_tick; void* portphy; void* miibus; void* ifname; void* ifp; TYPE_1__ info; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_UKSWITCH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct ukswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ukswitch_attach_phys (struct ukswitch_softc*) ; 
 int /*<<< orphan*/  ukswitch_tick (struct ukswitch_softc*) ; 

__attribute__((used)) static int
ukswitch_attach(device_t dev)
{
	struct ukswitch_softc *sc;
	int err = 0;

	sc = device_get_softc(dev);

	sc->sc_dev = dev;
	mtx_init(&sc->sc_mtx, "ukswitch", NULL, MTX_DEF);
	strlcpy(sc->info.es_name, device_get_desc(dev),
	    sizeof(sc->info.es_name));

	/* XXX Defaults */
	sc->numports = 6;
	sc->phymask = 0x0f;
	sc->phyoffset = 0;
	sc->cpuport = -1;
	sc->media = 100;

	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "numports", &sc->numports);
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "phymask", &sc->phymask);
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "phyoffset", &sc->phyoffset);
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "cpuport", &sc->cpuport);
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "media", &sc->media);

	/* Support only fast and giga ethernet. */
	if (sc->media != 100 && sc->media != 1000)
		sc->media = 100;

	if (sc->cpuport != -1)
		/* Always attach the cpu port. */
		sc->phymask |= (1 << sc->cpuport);

	/* We do not support any vlan groups. */
	sc->info.es_nvlangroups = 0;

	sc->ifp = malloc(sizeof(struct ifnet *) * sc->numports, M_UKSWITCH,
	    M_WAITOK | M_ZERO);
	sc->ifname = malloc(sizeof(char *) * sc->numports, M_UKSWITCH,
	    M_WAITOK | M_ZERO);
	sc->miibus = malloc(sizeof(device_t *) * sc->numports, M_UKSWITCH,
	    M_WAITOK | M_ZERO);
	sc->portphy = malloc(sizeof(int) * sc->numports, M_UKSWITCH,
	    M_WAITOK | M_ZERO);

	/*
	 * Attach the PHYs and complete the bus enumeration.
	 */
	err = ukswitch_attach_phys(sc);
	if (err != 0)
		return (err);

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	err = bus_generic_attach(dev);
	if (err != 0)
		return (err);
	
	callout_init(&sc->callout_tick, 0);

	ukswitch_tick(sc);
	
	return (err);
}