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
struct ifnet {int dummy; } ;
struct TYPE_2__ {int es_nvlangroups; int es_vlan_caps; int /*<<< orphan*/  es_name; } ;
struct adm6996fc_softc {int numports; int phymask; int cpuport; int media; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ * miibus; int /*<<< orphan*/ * portphy; int /*<<< orphan*/  callout_tick; TYPE_1__ info; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ETHERSWITCH_VLAN_DOT1Q ; 
 int ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_ADM6996FC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int adm6996fc_attach_phys (struct adm6996fc_softc*) ; 
 int /*<<< orphan*/  adm6996fc_tick (struct adm6996fc_softc*) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 struct adm6996fc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
adm6996fc_attach(device_t dev)
{
	struct adm6996fc_softc	*sc;
	int			 err;

	err = 0;
	sc = device_get_softc(dev);

	sc->sc_dev = dev;
	mtx_init(&sc->sc_mtx, "adm6996fc", NULL, MTX_DEF);
	strlcpy(sc->info.es_name, device_get_desc(dev),
	    sizeof(sc->info.es_name));

	/* ADM6996FC Defaults */
	sc->numports = 6;
	sc->phymask = 0x1f;
	sc->cpuport = 5;
	sc->media = 100;

	sc->info.es_nvlangroups = 16;
	sc->info.es_vlan_caps = ETHERSWITCH_VLAN_PORT | ETHERSWITCH_VLAN_DOT1Q;

	sc->ifp = malloc(sizeof(struct ifnet *) * sc->numports, M_ADM6996FC,
	    M_WAITOK | M_ZERO);
	sc->ifname = malloc(sizeof(char *) * sc->numports, M_ADM6996FC,
	    M_WAITOK | M_ZERO);
	sc->miibus = malloc(sizeof(device_t *) * sc->numports, M_ADM6996FC,
	    M_WAITOK | M_ZERO);
	sc->portphy = malloc(sizeof(int) * sc->numports, M_ADM6996FC,
	    M_WAITOK | M_ZERO);

	if (sc->ifp == NULL || sc->ifname == NULL || sc->miibus == NULL ||
	    sc->portphy == NULL) {
		err = ENOMEM;
		goto failed;
	}

	/*
	 * Attach the PHYs and complete the bus enumeration.
	 */
	err = adm6996fc_attach_phys(sc);
	if (err != 0)
		goto failed;

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	err = bus_generic_attach(dev);
	if (err != 0)
		goto failed;
	
	callout_init(&sc->callout_tick, 0);

	adm6996fc_tick(sc);
	
	return (0);

failed:
	if (sc->portphy != NULL)
		free(sc->portphy, M_ADM6996FC);
	if (sc->miibus != NULL)
		free(sc->miibus, M_ADM6996FC);
	if (sc->ifname != NULL)
		free(sc->ifname, M_ADM6996FC);
	if (sc->ifp != NULL)
		free(sc->ifp, M_ADM6996FC);

	return (err);
}