#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int es_nports; } ;
struct ukswitch_softc {int phymask; int* ifpport; int* portphy; int numports; TYPE_1__ info; int /*<<< orphan*/  sc_dev; TYPE_2__** ifp; int /*<<< orphan*/ ** miibus; scalar_t__ phyoffset; void** ifname; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int if_flags; int /*<<< orphan*/  if_xname; struct ukswitch_softc* if_softc; } ;

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
 int MII_NPHY ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  M_UKSWITCH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (char*,void*,int) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (TYPE_2__*,void*,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  ukswitch_ifmedia_sts ; 
 int /*<<< orphan*/  ukswitch_ifmedia_upd ; 

__attribute__((used)) static int
ukswitch_attach_phys(struct ukswitch_softc *sc)
{
	int phy, port = 0, err = 0;
	char name[IFNAMSIZ];

	/* PHYs need an interface, so we generate a dummy one */
	snprintf(name, IFNAMSIZ, "%sport", device_get_nameunit(sc->sc_dev));
	for (phy = 0; phy < MII_NPHY; phy++) {
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
		sc->ifname[port] = malloc(strlen(name)+1, M_UKSWITCH, M_WAITOK);
		bcopy(name, sc->ifname[port], strlen(name)+1);
		if_initname(sc->ifp[port], sc->ifname[port], port);
		sc->miibus[port] = malloc(sizeof(device_t), M_UKSWITCH,
		    M_WAITOK | M_ZERO);
		err = mii_attach(sc->sc_dev, sc->miibus[port], sc->ifp[port],
		    ukswitch_ifmedia_upd, ukswitch_ifmedia_sts, \
		    BMSR_DEFCAPMASK, phy + sc->phyoffset, MII_OFFSET_ANY, 0);
		DPRINTF(sc->sc_dev, "%s attached to pseudo interface %s\n",
		    device_get_nameunit(*sc->miibus[port]),
		    sc->ifp[port]->if_xname);
		if (err != 0) {
			device_printf(sc->sc_dev,
			    "attaching PHY %d failed\n",
			    phy);
			break;
		}
		sc->info.es_nports = port + 1;
		if (++port >= sc->numports)
			break;
	}
	return (err);
}