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
struct mii_softc {struct mii_data* mii_pdata; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_media_status; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int ANER_LPAN ; 
 int ANLPAR_10 ; 
 int ANLPAR_10_FD ; 
 int ANLPAR_T4 ; 
 int ANLPAR_TX ; 
 int ANLPAR_TX_FD ; 
 int BMCR_AUTOEN ; 
 int BMCR_ISO ; 
 int BMCR_LOOP ; 
 int BMSR_ACOMP ; 
 int BMSR_LINK ; 
 int IFM_100_T4 ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int IFM_LOOP ; 
 int IFM_NONE ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_ANER ; 
 int /*<<< orphan*/  MII_ANLPAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_NSPHY_PAR ; 
 int PAR_10 ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
nsphy_status(struct mii_softc *sc)
{
	struct mii_data *mii = sc->mii_pdata;
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int bmsr, bmcr, par, anlpar;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	bmsr = PHY_READ(sc, MII_BMSR) |
	    PHY_READ(sc, MII_BMSR);
	if (bmsr & BMSR_LINK)
		mii->mii_media_status |= IFM_ACTIVE;

	bmcr = PHY_READ(sc, MII_BMCR);
	if (bmcr & BMCR_ISO) {
		mii->mii_media_active |= IFM_NONE;
		mii->mii_media_status = 0;
		return;
	}

	if (bmcr & BMCR_LOOP)
		mii->mii_media_active |= IFM_LOOP;

	if (bmcr & BMCR_AUTOEN) {
		/*
		 * The PAR status bits are only valid if autonegotiation
		 * has completed (or it's disabled).
		 */
		if ((bmsr & BMSR_ACOMP) == 0) {
			/* Erg, still trying, I guess... */
			mii->mii_media_active |= IFM_NONE;
			return;
		}

		/*
		 * Argh.  The PAR doesn't seem to indicate duplex mode
		 * properly!  Determine media based on link partner's
		 * advertised capabilities.
		 */
		if (PHY_READ(sc, MII_ANER) & ANER_LPAN) {
			anlpar = PHY_READ(sc, MII_ANAR) &
			    PHY_READ(sc, MII_ANLPAR);
			if (anlpar & ANLPAR_TX_FD)
				mii->mii_media_active |= IFM_100_TX|IFM_FDX;
			else if (anlpar & ANLPAR_T4)
				mii->mii_media_active |= IFM_100_T4|IFM_HDX;
			else if (anlpar & ANLPAR_TX)
				mii->mii_media_active |= IFM_100_TX|IFM_HDX;
			else if (anlpar & ANLPAR_10_FD)
				mii->mii_media_active |= IFM_10_T|IFM_FDX;
			else if (anlpar & ANLPAR_10)
				mii->mii_media_active |= IFM_10_T|IFM_HDX;
			else
				mii->mii_media_active |= IFM_NONE;
			if ((mii->mii_media_active & IFM_FDX) != 0)
				mii->mii_media_active |=
				    mii_phy_flowstatus(sc);
			return;
		}

		/*
		 * Link partner is not capable of autonegotiation.
		 * We will never be in full-duplex mode if this is
		 * the case, so reading the PAR is OK.
		 */
		par = PHY_READ(sc, MII_NSPHY_PAR);
		if (par & PAR_10)
			mii->mii_media_active |= IFM_10_T;
		else
			mii->mii_media_active |= IFM_100_TX;
		mii->mii_media_active |= IFM_HDX;
	} else
		mii->mii_media_active = ife->ifm_media;
}