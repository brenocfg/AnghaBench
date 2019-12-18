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
struct TYPE_2__ {int es_nvlangroups; int es_vlan_caps; int /*<<< orphan*/  es_name; } ;
struct ksz8995ma_softc {int numports; int phymask; int cpuport; int media; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ * miibus; int /*<<< orphan*/ * portphy; scalar_t__ vlan_mode; int /*<<< orphan*/  callout_tick; TYPE_1__ info; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ETHERSWITCH_VLAN_DOT1Q ; 
 int ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  KSZ8995MA_CID1 ; 
 int /*<<< orphan*/  KSZ8995MA_GC3 ; 
 int KSZ8995MA_MAX_PORT ; 
 int KSZ8995MA_START ; 
 int KSZ8995MA_VLAN_ENABLE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_KSZ8995MA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct ksz8995ma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ksz8995ma_attach_phys (struct ksz8995ma_softc*) ; 
 int /*<<< orphan*/  ksz8995ma_portvlanreset (int /*<<< orphan*/ ) ; 
 int ksz8995ma_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz8995ma_tick (struct ksz8995ma_softc*) ; 
 int /*<<< orphan*/  ksz8995ma_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ksz8995ma_attach(device_t dev)
{
	struct ksz8995ma_softc	*sc;
	int			 err, reg;

	err = 0;
	sc = device_get_softc(dev);

	sc->sc_dev = dev;
	mtx_init(&sc->sc_mtx, "ksz8995ma", NULL, MTX_DEF);
	strlcpy(sc->info.es_name, device_get_desc(dev),
	    sizeof(sc->info.es_name));

	/* KSZ8995MA Defaults */
	sc->numports = KSZ8995MA_MAX_PORT;
	sc->phymask = (1 << (KSZ8995MA_MAX_PORT + 1)) - 1;
	sc->cpuport = -1;
	sc->media = 100;

	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "cpuport", &sc->cpuport);

	sc->info.es_nvlangroups = 16;
	sc->info.es_vlan_caps = ETHERSWITCH_VLAN_PORT | ETHERSWITCH_VLAN_DOT1Q;

	sc->ifp = malloc(sizeof(struct ifnet *) * sc->numports, M_KSZ8995MA,
	    M_WAITOK | M_ZERO);
	sc->ifname = malloc(sizeof(char *) * sc->numports, M_KSZ8995MA,
	    M_WAITOK | M_ZERO);
	sc->miibus = malloc(sizeof(device_t *) * sc->numports, M_KSZ8995MA,
	    M_WAITOK | M_ZERO);
	sc->portphy = malloc(sizeof(int) * sc->numports, M_KSZ8995MA,
	    M_WAITOK | M_ZERO);

	if (sc->ifp == NULL || sc->ifname == NULL || sc->miibus == NULL ||
	    sc->portphy == NULL) {
		err = ENOMEM;
		goto failed;
	}

	/*
	 * Attach the PHYs and complete the bus enumeration.
	 */
	err = ksz8995ma_attach_phys(sc);
	if (err != 0)
		goto failed;

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	err = bus_generic_attach(dev);
	if (err != 0)
		goto failed;
	
	callout_init(&sc->callout_tick, 0);

	ksz8995ma_tick(sc);
	
	/* start switch */
	sc->vlan_mode = 0;
	reg = ksz8995ma_readreg(dev, KSZ8995MA_GC3);
	ksz8995ma_writereg(dev, KSZ8995MA_GC3, 
	    reg & ~KSZ8995MA_VLAN_ENABLE);
	ksz8995ma_portvlanreset(dev);
	ksz8995ma_writereg(dev, KSZ8995MA_CID1, KSZ8995MA_START);

	return (0);

failed:
	if (sc->portphy != NULL)
		free(sc->portphy, M_KSZ8995MA);
	if (sc->miibus != NULL)
		free(sc->miibus, M_KSZ8995MA);
	if (sc->ifname != NULL)
		free(sc->ifname, M_KSZ8995MA);
	if (sc->ifp != NULL)
		free(sc->ifp, M_KSZ8995MA);

	return (err);
}