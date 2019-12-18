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
struct mii_softc {int /*<<< orphan*/  mii_dev; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_ifp; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_UP ; 
#define  IFM_100_TX 132 
#define  IFM_10_T 131 
 int const IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  MIIBUS_STATCHG (int /*<<< orphan*/ ) ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
pnphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		/*
		 * If the interface is not up, don't do anything.
		 */
		if ((if_getflags(mii->mii_ifp) & IFF_UP) == 0)
			break;

		/*
		 * Note that auto-negotiation is broken on this chip.
		 */
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_100_TX:
			mii->mii_media_active = IFM_ETHER | IFM_100_TX;
			if ((ife->ifm_media & IFM_FDX) != 0)
				mii->mii_media_active |= IFM_FDX;
			MIIBUS_STATCHG(sc->mii_dev);
			return (0);
		case IFM_10_T:
			mii->mii_media_active = IFM_ETHER | IFM_10_T;
			if ((ife->ifm_media & IFM_FDX) != 0)
				mii->mii_media_active |= IFM_FDX;
			MIIBUS_STATCHG(sc->mii_dev);
			return (0);
		default:
			return (EINVAL);
		}
		break;

	case MII_TICK:
		/*
		 * Is the interface even up?
		 */
		if ((if_getflags(mii->mii_ifp) & IFF_UP) == 0)
			return (0);

		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}