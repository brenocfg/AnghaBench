#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mii_softc {int /*<<< orphan*/  mii_ticks; struct mii_data* mii_pdata; } ;
struct mii_data {scalar_t__ mii_media_active; int /*<<< orphan*/  mii_media_status; } ;

/* Variables and functions */
 int BMCR_ISO ; 
 int BMCR_LOOP ; 
 int GTSR_MS_RES ; 
 scalar_t__ IFM_1000_T ; 
 scalar_t__ IFM_100_TX ; 
 scalar_t__ IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 scalar_t__ IFM_ETHER ; 
 int IFM_ETH_MASTER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 scalar_t__ IFM_LOOP ; 
 scalar_t__ IFM_NONE ; 
 scalar_t__ IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  JMPHY_SSR ; 
 int JMPHY_SSR_DUPLEX ; 
 int JMPHY_SSR_LINK_UP ; 
 int JMPHY_SSR_SPD_DPLX_RESOLVED ; 
#define  JMPHY_SSR_SPEED_10 130 
#define  JMPHY_SSR_SPEED_100 129 
#define  JMPHY_SSR_SPEED_1000 128 
 int JMPHY_SSR_SPEED_MASK ; 
 int /*<<< orphan*/  MII_100T2SR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
jmphy_status(struct mii_softc *sc)
{
	struct mii_data *mii = sc->mii_pdata;
	int bmcr, ssr;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	ssr = PHY_READ(sc, JMPHY_SSR);
	if ((ssr & JMPHY_SSR_LINK_UP) != 0)
		mii->mii_media_status |= IFM_ACTIVE;

	bmcr = PHY_READ(sc, MII_BMCR);
	if ((bmcr & BMCR_ISO) != 0) {
		mii->mii_media_active |= IFM_NONE;
		mii->mii_media_status = 0;
		return;
	}

	if ((bmcr & BMCR_LOOP) != 0)
		mii->mii_media_active |= IFM_LOOP;

	if ((ssr & JMPHY_SSR_SPD_DPLX_RESOLVED) == 0) {
		/* Erg, still trying, I guess... */
		mii->mii_media_active |= IFM_NONE;
		return;
	}

	switch ((ssr & JMPHY_SSR_SPEED_MASK)) {
	case JMPHY_SSR_SPEED_1000:
		mii->mii_media_active |= IFM_1000_T;
		/*
		 * jmphy(4) got a valid link so reset mii_ticks.
		 * Resetting mii_ticks is needed in order to
		 * detect link loss after auto-negotiation.
		 */
		sc->mii_ticks = 0;
		break;
	case JMPHY_SSR_SPEED_100:
		mii->mii_media_active |= IFM_100_TX;
		sc->mii_ticks = 0;
		break;
	case JMPHY_SSR_SPEED_10:
		mii->mii_media_active |= IFM_10_T;
		sc->mii_ticks = 0;
		break;
	default:
		mii->mii_media_active |= IFM_NONE;
		return;
	}

	if ((ssr & JMPHY_SSR_DUPLEX) != 0)
		mii->mii_media_active |= IFM_FDX | mii_phy_flowstatus(sc);
	else
		mii->mii_media_active |= IFM_HDX;

	if (IFM_SUBTYPE(mii->mii_media_active) == IFM_1000_T) {
		if ((PHY_READ(sc, MII_100T2SR) & GTSR_MS_RES) != 0)
			mii->mii_media_active |= IFM_ETH_MASTER;
	}
}