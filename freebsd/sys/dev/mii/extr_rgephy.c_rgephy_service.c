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
struct mii_softc {int mii_flags; scalar_t__ mii_media_active; scalar_t__ mii_media_status; int /*<<< orphan*/  mii_ticks; int /*<<< orphan*/  mii_anegticks; } ;
struct TYPE_2__ {int ifm_media; struct ifmedia_entry* ifm_cur; } ;
struct mii_data {scalar_t__ mii_media_active; scalar_t__ mii_media_status; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int BMCR_ISO ; 
 int BMCR_PDOWN ; 
 int EINVAL ; 
#define  IFM_1000_T 135 
#define  IFM_100_TX 134 
#define  IFM_10_T 133 
#define  IFM_AUTO 132 
 int IFM_ETH_MASTER ; 
 int IFM_FDX ; 
 int IFM_FLAG0 ; 
 int IFM_FLOW ; 
#define  IFM_NONE 131 
 int const IFM_SUBTYPE (int) ; 
 int MIIF_FORCEPAUSE ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int RGEPHY_1000CTL_AFD ; 
 int RGEPHY_1000CTL_AHD ; 
 int RGEPHY_1000CTL_MSC ; 
 int RGEPHY_1000CTL_MSE ; 
 int RGEPHY_ANAR_10 ; 
 int RGEPHY_ANAR_10_FD ; 
 int RGEPHY_ANAR_ASP ; 
 int RGEPHY_ANAR_PC ; 
 int RGEPHY_ANAR_TX ; 
 int RGEPHY_ANAR_TX_FD ; 
 int RGEPHY_BMCR_AUTOEN ; 
 int RGEPHY_BMCR_FDX ; 
 int RGEPHY_BMCR_STARTNEG ; 
 int /*<<< orphan*/  RGEPHY_MII_1000CTL ; 
 int /*<<< orphan*/  RGEPHY_MII_ANAR ; 
 int /*<<< orphan*/  RGEPHY_MII_BMCR ; 
 int RGEPHY_S10 ; 
 int RGEPHY_S100 ; 
 int RGEPHY_S1000 ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 
 int /*<<< orphan*/  rgephy_linkup (struct mii_softc*) ; 
 int /*<<< orphan*/  rgephy_load_dspcode (struct mii_softc*) ; 
 int /*<<< orphan*/  rgephy_loop (struct mii_softc*) ; 
 int /*<<< orphan*/  rgephy_mii_phy_auto (struct mii_softc*,int) ; 

__attribute__((used)) static int
rgephy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int speed, gig, anar;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		PHY_RESET(sc);	/* XXX hardware bug work-around */

		anar = PHY_READ(sc, RGEPHY_MII_ANAR);
		anar &= ~(RGEPHY_ANAR_PC | RGEPHY_ANAR_ASP |
		    RGEPHY_ANAR_TX_FD | RGEPHY_ANAR_TX |
		    RGEPHY_ANAR_10_FD | RGEPHY_ANAR_10);

		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
#ifdef foo
			/*
			 * If we're already in auto mode, just return.
			 */
			if (PHY_READ(sc, RGEPHY_MII_BMCR) & RGEPHY_BMCR_AUTOEN)
				return (0);
#endif
			(void)rgephy_mii_phy_auto(sc, ife->ifm_media);
			break;
		case IFM_1000_T:
			speed = RGEPHY_S1000;
			goto setit;
		case IFM_100_TX:
			speed = RGEPHY_S100;
			anar |= RGEPHY_ANAR_TX_FD | RGEPHY_ANAR_TX;
			goto setit;
		case IFM_10_T:
			speed = RGEPHY_S10;
			anar |= RGEPHY_ANAR_10_FD | RGEPHY_ANAR_10;
setit:
			if ((ife->ifm_media & IFM_FLOW) != 0 &&
			    (mii->mii_media.ifm_media & IFM_FLAG0) != 0)
				return (EINVAL);

			if ((ife->ifm_media & IFM_FDX) != 0) {
				speed |= RGEPHY_BMCR_FDX;
				gig = RGEPHY_1000CTL_AFD;
				anar &= ~(RGEPHY_ANAR_TX | RGEPHY_ANAR_10);
				if ((ife->ifm_media & IFM_FLOW) != 0 ||
				    (sc->mii_flags & MIIF_FORCEPAUSE) != 0)
					anar |=
					    RGEPHY_ANAR_PC | RGEPHY_ANAR_ASP;
			} else {
				gig = RGEPHY_1000CTL_AHD;
				anar &=
				    ~(RGEPHY_ANAR_TX_FD | RGEPHY_ANAR_10_FD);
			}
			if (IFM_SUBTYPE(ife->ifm_media) == IFM_1000_T) {
				gig |= RGEPHY_1000CTL_MSE;
				if ((ife->ifm_media & IFM_ETH_MASTER) != 0)
				    gig |= RGEPHY_1000CTL_MSC;
			} else {
				gig = 0;
				anar &= ~RGEPHY_ANAR_ASP;
			}
			if ((mii->mii_media.ifm_media & IFM_FLAG0) == 0)
				speed |=
				    RGEPHY_BMCR_AUTOEN | RGEPHY_BMCR_STARTNEG;
			rgephy_loop(sc);
			PHY_WRITE(sc, RGEPHY_MII_1000CTL, gig);
			PHY_WRITE(sc, RGEPHY_MII_ANAR, anar);
			PHY_WRITE(sc, RGEPHY_MII_BMCR, speed);
			break;
		case IFM_NONE:
			PHY_WRITE(sc, MII_BMCR, BMCR_ISO | BMCR_PDOWN);
			break;
		default:
			return (EINVAL);
		}
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
		 * Check to see if we have link.  If we do, we don't
		 * need to restart the autonegotiation process.
		 */
		if (rgephy_linkup(sc) != 0) {
			sc->mii_ticks = 0;
			break;
		}

		/* Announce link loss right after it happens. */
		if (sc->mii_ticks++ == 0)
			break;

		/* Only retry autonegotiation every mii_anegticks seconds. */
		if (sc->mii_ticks <= sc->mii_anegticks)
			return (0);

		sc->mii_ticks = 0;
		rgephy_mii_phy_auto(sc, ife->ifm_media);
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/*
	 * Callback if something changed. Note that we need to poke
	 * the DSP on the RealTek PHYs if the media changes.
	 *
	 */
	if (sc->mii_media_active != mii->mii_media_active ||
	    sc->mii_media_status != mii->mii_media_status ||
	    cmd == MII_MEDIACHG) {
		rgephy_load_dspcode(sc);
	}
	mii_phy_update(sc, cmd);
	return (0);
}