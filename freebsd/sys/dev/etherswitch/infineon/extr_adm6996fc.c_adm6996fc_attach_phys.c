#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int es_nports; } ;
struct adm6996fc_softc {int numports; int phymask; int* ifpport; int* portphy; int cpuport; int /*<<< orphan*/ ** miibus; int /*<<< orphan*/ ** ifname; TYPE_2__** ifp; int /*<<< orphan*/  sc_dev; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {int if_flags; int /*<<< orphan*/  if_xname; struct adm6996fc_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_RUNNING ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  M_ADM6996FC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  adm6996fc_ifmedia_sts ; 
 int /*<<< orphan*/  adm6996fc_ifmedia_upd ; 
 int adm6996fc_portforphy (struct adm6996fc_softc*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (TYPE_2__*) ; 
 int /*<<< orphan*/  if_initname (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
adm6996fc_attach_phys(struct adm6996fc_softc *sc)
{
	int phy, port, err;
	char name[IFNAMSIZ];

	port = 0;
	err = 0;
	/* PHYs need an interface, so we generate a dummy one */
	snprintf(name, IFNAMSIZ, "%sport", device_get_nameunit(sc->sc_dev));
	for (phy = 0; phy < sc->numports; phy++) {
		if (((1 << phy) & sc->phymask) == 0)
			continue;
		sc->ifpport[phy] = port;
		sc->portphy[port] = phy;
		sc->ifp[port] = if_alloc(IFT_ETHER);
		if (sc->ifp[port] == NULL) {
			device_printf(sc->sc_dev, "couldn't allocate ifnet structure\n");
			err = ENOMEM;
			break;
		}

		sc->ifp[port]->if_softc = sc;
		sc->ifp[port]->if_flags |= IFF_UP | IFF_BROADCAST |
		    IFF_DRV_RUNNING | IFF_SIMPLEX;
		if_initname(sc->ifp[port], name, port);
		sc->miibus[port] = malloc(sizeof(device_t), M_ADM6996FC,
		    M_WAITOK | M_ZERO);
		if (sc->miibus[port] == NULL) {
			err = ENOMEM;
			goto failed;
		}
		err = mii_attach(sc->sc_dev, sc->miibus[port], sc->ifp[port],
		    adm6996fc_ifmedia_upd, adm6996fc_ifmedia_sts, \
		    BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY, 0);
		DPRINTF(sc->sc_dev, "%s attached to pseudo interface %s\n",
		    device_get_nameunit(*sc->miibus[port]),
		    sc->ifp[port]->if_xname);
		if (err != 0) {
			device_printf(sc->sc_dev,
			    "attaching PHY %d failed\n",
			    phy);
			goto failed;
		}
		++port;
	}
	sc->info.es_nports = port;
	if (sc->cpuport != -1) {
		/* assume cpuport is last one */
		sc->ifpport[sc->cpuport] = port;
		sc->portphy[port] = sc->cpuport;
		++sc->info.es_nports;
	}
	return (0);

failed:
	for (phy = 0; phy < sc->numports; phy++) {
		if (((1 << phy) & sc->phymask) == 0)
			continue;
		port = adm6996fc_portforphy(sc, phy);
		if (sc->miibus[port] != NULL)
			device_delete_child(sc->sc_dev, (*sc->miibus[port]));
		if (sc->ifp[port] != NULL)
			if_free(sc->ifp[port]);
		if (sc->ifname[port] != NULL)
			free(sc->ifname[port], M_ADM6996FC);
		if (sc->miibus[port] != NULL)
			free(sc->miibus[port], M_ADM6996FC);
	}
	return (err);
}