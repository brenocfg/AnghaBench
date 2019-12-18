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
struct mii_softc {int mii_flags; struct mii_data* mii_pdata; } ;
struct mii_data {scalar_t__ mii_media_active; int /*<<< orphan*/  mii_media_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_1GSR ; 
 int E1000_1GSR_MS_CONFIG_RES ; 
 int /*<<< orphan*/  E1000_CR ; 
 int E1000_CR_AUTO_NEG_ENABLE ; 
 int E1000_CR_LOOPBACK ; 
 int /*<<< orphan*/  E1000_SR ; 
 int E1000_SR_LINK_STATUS ; 
 int /*<<< orphan*/  E1000_SSR ; 
#define  E1000_SSR_1000MBS 130 
#define  E1000_SSR_100MBS 129 
#define  E1000_SSR_10MBS 128 
 int E1000_SSR_DUPLEX ; 
 int E1000_SSR_SPD_DPLX_RESOLVED ; 
 int E1000_SSR_SPEED ; 
 scalar_t__ IFM_1000_SX ; 
 scalar_t__ IFM_1000_T ; 
 scalar_t__ IFM_100_TX ; 
 scalar_t__ IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_ETH_MASTER ; 
 scalar_t__ IFM_FDX ; 
 scalar_t__ IFM_HDX ; 
 scalar_t__ IFM_LOOP ; 
 scalar_t__ IFM_NONE ; 
 scalar_t__ IFM_SUBTYPE (scalar_t__) ; 
 int MIIF_HAVEFIBER ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
e1000phy_status(struct mii_softc *sc)
{
	struct mii_data *mii = sc->mii_pdata;
	int bmcr, bmsr, ssr;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	bmsr = PHY_READ(sc, E1000_SR) | PHY_READ(sc, E1000_SR);
	bmcr = PHY_READ(sc, E1000_CR);
	ssr = PHY_READ(sc, E1000_SSR);

	if (bmsr & E1000_SR_LINK_STATUS)
		mii->mii_media_status |= IFM_ACTIVE;

	if (bmcr & E1000_CR_LOOPBACK)
		mii->mii_media_active |= IFM_LOOP;

	if ((bmcr & E1000_CR_AUTO_NEG_ENABLE) != 0 &&
	    (ssr & E1000_SSR_SPD_DPLX_RESOLVED) == 0) {
		/* Erg, still trying, I guess... */
		mii->mii_media_active |= IFM_NONE;
		return;
	}

	if ((sc->mii_flags & MIIF_HAVEFIBER) == 0) {
		switch (ssr & E1000_SSR_SPEED) {
		case E1000_SSR_1000MBS:
			mii->mii_media_active |= IFM_1000_T;
			break;
		case E1000_SSR_100MBS:
			mii->mii_media_active |= IFM_100_TX;
			break;
		case E1000_SSR_10MBS:
			mii->mii_media_active |= IFM_10_T;
			break;
		default:
			mii->mii_media_active |= IFM_NONE;
			return;
		}
	} else {
		/*
		 * Some fiber PHY(88E1112) does not seem to set resolved
		 * speed so always assume we've got IFM_1000_SX.
		 */
		mii->mii_media_active |= IFM_1000_SX;
	}

	if (ssr & E1000_SSR_DUPLEX) {
		mii->mii_media_active |= IFM_FDX;
		if ((sc->mii_flags & MIIF_HAVEFIBER) == 0)
			mii->mii_media_active |= mii_phy_flowstatus(sc);
	} else
		mii->mii_media_active |= IFM_HDX;

	if (IFM_SUBTYPE(mii->mii_media_active) == IFM_1000_T) {
		if (((PHY_READ(sc, E1000_1GSR) | PHY_READ(sc, E1000_1GSR)) &
		    E1000_1GSR_MS_CONFIG_RES) != 0)
			mii->mii_media_active |= IFM_ETH_MASTER;
	}
}