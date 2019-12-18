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
 int DIAG_DUPLEX ; 
 int DIAG_NEGFAIL ; 
 int DIAG_RATE_100 ; 
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
 int /*<<< orphan*/  MII_ANLPAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_DIAG ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
tdkphy_status(struct mii_softc *phy)
{
	struct mii_data *mii = phy->mii_pdata;
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int bmsr, bmcr, anlpar, diag;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	bmsr = PHY_READ(phy, MII_BMSR) | PHY_READ(phy, MII_BMSR);
	if (bmsr & BMSR_LINK)
		mii->mii_media_status |= IFM_ACTIVE;

	bmcr = PHY_READ(phy, MII_BMCR);
	if (bmcr & BMCR_ISO) {
		mii->mii_media_active |= IFM_NONE;
		mii->mii_media_status = 0;
		return;
	}

	if (bmcr & BMCR_LOOP)
		mii->mii_media_active |= IFM_LOOP;

	if (bmcr & BMCR_AUTOEN) {
		/*
		 * NWay autonegotiation takes the highest-order common
		 * bit of the ANAR and ANLPAR (i.e. best media advertised
		 * both by us and our link partner).
		 */
		if ((bmsr & BMSR_ACOMP) == 0) {
			/* Erg, still trying, I guess... */
			mii->mii_media_active |= IFM_NONE;
			return;
		}

		anlpar = PHY_READ(phy, MII_ANAR) & PHY_READ(phy, MII_ANLPAR);
		/*
		 * ANLPAR doesn't get set on my card, but we check it anyway,
		 * since it is mentioned in the 78Q2120 specs.
		 */
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
		else {
			/*
			 * ANLPAR isn't set, which leaves two possibilities:
			 * 1) Auto negotiation failed
			 * 2) Auto negotiation completed, but the card forgot
			 *    to set ANLPAR.
			 * So we check the MII_DIAG(18) register...
			 */
			diag = PHY_READ(phy, MII_DIAG);
			if (diag & DIAG_NEGFAIL) /* assume 10baseT if no neg */
				mii->mii_media_active |= IFM_10_T|IFM_HDX;
			else {
				if (diag & DIAG_DUPLEX)
					mii->mii_media_active |= IFM_FDX;
				else
					mii->mii_media_active |= IFM_HDX;
				if (diag & DIAG_RATE_100)
					mii->mii_media_active |= IFM_100_TX;
				else
					mii->mii_media_active |= IFM_10_T;
			}
		}
		if ((mii->mii_media_active & IFM_FDX) != 0)
			mii->mii_media_active |= mii_phy_flowstatus(phy);
	} else
		mii->mii_media_active = ife->ifm_media;
}