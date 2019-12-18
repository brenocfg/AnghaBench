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
typedef  int uint32_t ;
struct mii_softc {int /*<<< orphan*/  mii_ticks; int /*<<< orphan*/  mii_anegticks; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int BMSR_LINK ; 
 int EINVAL ; 
#define  IFM_1000_T 134 
#define  IFM_100_TX 133 
#define  IFM_10_T 132 
#define  IFM_AUTO 131 
 int IFM_ETH_MASTER ; 
 int IFM_FDX ; 
 int const IFM_SUBTYPE (int) ; 
 int IP1000PHY_1000CR_1000T ; 
 int IP1000PHY_1000CR_1000T_FDX ; 
 int IP1000PHY_1000CR_MANUAL ; 
 int IP1000PHY_1000CR_MASTER ; 
 int IP1000PHY_1000CR_MMASTER ; 
 int IP1000PHY_BMCR_10 ; 
 int IP1000PHY_BMCR_100 ; 
 int IP1000PHY_BMCR_1000 ; 
 int IP1000PHY_BMCR_FDX ; 
 int /*<<< orphan*/  IP1000PHY_MII_1000CR ; 
 int /*<<< orphan*/  IP1000PHY_MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip1000phy_mii_phy_auto (struct mii_softc*,int) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
ip1000phy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	uint32_t gig, reg, speed;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		PHY_RESET(sc);
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
			(void)ip1000phy_mii_phy_auto(sc, ife->ifm_media);
			goto done;

		case IFM_1000_T:
			/*
			 * XXX
			 * Manual 1000baseT setting doesn't seem to work.
			 */
			speed = IP1000PHY_BMCR_1000;
			break;

		case IFM_100_TX:
			speed = IP1000PHY_BMCR_100;
			break;

		case IFM_10_T:
			speed = IP1000PHY_BMCR_10;
			break;

		default:
			return (EINVAL);
		}

		if ((ife->ifm_media & IFM_FDX) != 0) {
			speed |= IP1000PHY_BMCR_FDX;
			gig = IP1000PHY_1000CR_1000T_FDX;
		} else
			gig = IP1000PHY_1000CR_1000T;

		if (IFM_SUBTYPE(ife->ifm_media) == IFM_1000_T) {
			gig |=
			    IP1000PHY_1000CR_MASTER | IP1000PHY_1000CR_MANUAL;
			if ((ife->ifm_media & IFM_ETH_MASTER) != 0)
				gig |= IP1000PHY_1000CR_MMASTER;
		} else
			gig = 0;
		PHY_WRITE(sc, IP1000PHY_MII_1000CR, gig);
		PHY_WRITE(sc, IP1000PHY_MII_BMCR, speed);

done:
		break;

	case MII_TICK:
		/*
		 * Only used for autonegotiation.
		 */
		if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO) {
			sc->mii_ticks = 0;
			break;
		}

		/*
		 * check for link.
		 */
		reg = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
		if (reg & BMSR_LINK) {
			sc->mii_ticks = 0;
			break;
		}

		/* Announce link loss right after it happens */
		if (sc->mii_ticks++ == 0)
			break;

		/*
		 * Only retry autonegotiation every mii_anegticks seconds.
		 */
		if (sc->mii_ticks <= sc->mii_anegticks)
			break;

		sc->mii_ticks = 0;
		ip1000phy_mii_phy_auto(sc, ife->ifm_media);
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}