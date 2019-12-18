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
struct e6060sw_softc {int numports; int phymask; int* ifpport; int* portphy; int cpuport; TYPE_1__ info; int /*<<< orphan*/  sc_dev; TYPE_2__** ifp; int /*<<< orphan*/ ** miibus; scalar_t__ smi_offset; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int if_flags; int /*<<< orphan*/  if_xname; struct e6060sw_softc* if_softc; } ;

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
 int /*<<< orphan*/  M_E6060SW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  e6060sw_ifmedia_sts ; 
 int /*<<< orphan*/  e6060sw_ifmedia_upd ; 
 TYPE_2__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
e6060sw_attach_phys(struct e6060sw_softc *sc)
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
		sc->miibus[port] = malloc(sizeof(device_t), M_E6060SW,
		    M_WAITOK | M_ZERO);
		err = mii_attach(sc->sc_dev, sc->miibus[port], sc->ifp[port],
		    e6060sw_ifmedia_upd, e6060sw_ifmedia_sts, \
		    BMSR_DEFCAPMASK, phy + sc->smi_offset, MII_OFFSET_ANY, 0);
		DPRINTF(sc->sc_dev, "%s attached to pseudo interface %s\n",
		    device_get_nameunit(*sc->miibus[port]),
		    sc->ifp[port]->if_xname);
		if (err != 0) {
			device_printf(sc->sc_dev,
			    "attaching PHY %d failed\n",
			    phy);
			break;
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
	return (err);
}