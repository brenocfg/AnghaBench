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
struct mii_softc {scalar_t__ mii_media_active; scalar_t__ mii_media_status; int mii_mpd_oui; int mii_mpd_rev; int /*<<< orphan*/  mii_mpd_model; int /*<<< orphan*/  mii_ticks; int /*<<< orphan*/  mii_anegticks; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {scalar_t__ mii_media_active; scalar_t__ mii_media_status; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int BMSR_LINK ; 
 int EINVAL ; 
#define  IFM_1000_SX 141 
#define  IFM_1000_T 140 
#define  IFM_100_TX 139 
#define  IFM_10_T 138 
#define  IFM_2500_SX 137 
#define  IFM_AUTO 136 
 int const IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BMSR ; 
#define  MII_MEDIACHG 135 
#define  MII_MODEL_BROADCOM_BCM5400 134 
#define  MII_MODEL_BROADCOM_BCM5401 133 
#define  MII_MODEL_BROADCOM_BCM5411 132 
#define  MII_MODEL_BROADCOM_BCM54K2 131 
#define  MII_OUI_BROADCOM 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  bcm5401_load_dspcode (struct mii_softc*) ; 
 int /*<<< orphan*/  bcm5411_load_dspcode (struct mii_softc*) ; 
 int /*<<< orphan*/  bcm54k2_load_dspcode (struct mii_softc*) ; 
 int /*<<< orphan*/  brgphy_mii_phy_auto (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brgphy_setmedia (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
brgphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int val;

	switch (cmd) {
	case MII_POLLSTAT:
		break;
	case MII_MEDIACHG:
		/* Todo: Why is this here?  Is it really needed? */
		PHY_RESET(sc);	/* XXX hardware bug work-around */

		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
			brgphy_mii_phy_auto(sc, ife->ifm_media);
			break;
		case IFM_2500_SX:
		case IFM_1000_SX:
		case IFM_1000_T:
		case IFM_100_TX:
		case IFM_10_T:
			brgphy_setmedia(sc, ife->ifm_media);
			break;
		default:
			return (EINVAL);
		}
		break;
	case MII_TICK:
		/* Bail if autoneg isn't in process. */
		if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO) {
			sc->mii_ticks = 0;
			break;
		}

		/*
		 * Check to see if we have link.  If we do, we don't
		 * need to restart the autonegotiation process.
		 */
		val = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
		if (val & BMSR_LINK) {
			sc->mii_ticks = 0;	/* Reset autoneg timer. */
			break;
		}

		/* Announce link loss right after it happens. */
		if (sc->mii_ticks++ == 0)
			break;

		/* Only retry autonegotiation every mii_anegticks seconds. */
		if (sc->mii_ticks <= sc->mii_anegticks)
			break;


		/* Retry autonegotiation */
		sc->mii_ticks = 0;
		brgphy_mii_phy_auto(sc, ife->ifm_media);
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/*
	 * Callback if something changed. Note that we need to poke
	 * the DSP on the Broadcom PHYs if the media changes.
	 */
	if (sc->mii_media_active != mii->mii_media_active ||
	    sc->mii_media_status != mii->mii_media_status ||
	    cmd == MII_MEDIACHG) {
		switch (sc->mii_mpd_oui) {
		case MII_OUI_BROADCOM:
			switch (sc->mii_mpd_model) {
			case MII_MODEL_BROADCOM_BCM5400:
				bcm5401_load_dspcode(sc);
				break;
			case MII_MODEL_BROADCOM_BCM5401:
				if (sc->mii_mpd_rev == 1 || sc->mii_mpd_rev == 3)
					bcm5401_load_dspcode(sc);
				break;
			case MII_MODEL_BROADCOM_BCM5411:
				bcm5411_load_dspcode(sc);
				break;
			case MII_MODEL_BROADCOM_BCM54K2:
				bcm54k2_load_dspcode(sc);
				break;
			}
			break;
		}
	}
	mii_phy_update(sc, cmd);
	return (0);
}