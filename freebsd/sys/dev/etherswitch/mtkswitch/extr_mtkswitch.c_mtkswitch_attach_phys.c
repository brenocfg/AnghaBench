#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtkswitch_softc {int numphys; unsigned int phymap; TYPE_1__** ifp; int /*<<< orphan*/ ** miibus; int /*<<< orphan*/ * sc_dev; int /*<<< orphan*/ ** ifname; } ;
struct TYPE_4__ {int if_flags; int /*<<< orphan*/  if_xname; struct mtkswitch_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_RUNNING ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 char* device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtkswitch_ifmedia_sts ; 
 int /*<<< orphan*/  mtkswitch_ifmedia_upd ; 
 int /*<<< orphan*/  mtkswitch_portforphy (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
mtkswitch_attach_phys(struct mtkswitch_softc *sc)
{
	int phy, err = 0;
	char name[IFNAMSIZ];

	/* PHYs need an interface, so we generate a dummy one */
	snprintf(name, IFNAMSIZ, "%sport", device_get_nameunit(sc->sc_dev));
	for (phy = 0; phy < sc->numphys; phy++) {
		if ((sc->phymap & (1u << phy)) == 0) {
			sc->ifp[phy] = NULL;
			sc->ifname[phy] = NULL;
			sc->miibus[phy] = NULL;
			continue;
		}
		sc->ifp[phy] = if_alloc(IFT_ETHER);
		if (sc->ifp[phy] == NULL) {
			device_printf(sc->sc_dev, "couldn't allocate ifnet structure\n");
			err = ENOMEM;
			break;
		}

		sc->ifp[phy]->if_softc = sc;
		sc->ifp[phy]->if_flags |= IFF_UP | IFF_BROADCAST |
		    IFF_DRV_RUNNING | IFF_SIMPLEX;
		sc->ifname[phy] = malloc(strlen(name) + 1, M_DEVBUF, M_WAITOK);
		bcopy(name, sc->ifname[phy], strlen(name) + 1);
		if_initname(sc->ifp[phy], sc->ifname[phy],
		    mtkswitch_portforphy(phy));
		err = mii_attach(sc->sc_dev, &sc->miibus[phy], sc->ifp[phy],
		    mtkswitch_ifmedia_upd, mtkswitch_ifmedia_sts,
		    BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY, 0);
		if (err != 0) {
			device_printf(sc->sc_dev,
			    "attaching PHY %d failed\n",
			    phy);
		} else {
			DPRINTF(sc->sc_dev, "%s attached to pseudo interface "
			    "%s\n", device_get_nameunit(sc->miibus[phy]),
			    sc->ifp[phy]->if_xname);
		}
	}
	return (err);
}