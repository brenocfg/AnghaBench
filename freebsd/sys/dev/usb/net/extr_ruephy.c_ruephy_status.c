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
 int BMCR_AUTOEN ; 
 int BMCR_ISO ; 
 int BMSR_ACOMP ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int IFM_NONE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUEPHY_MII_MSR ; 
 int RUEPHY_MSR_DUPLEX ; 
 int RUEPHY_MSR_LINK ; 
 int RUEPHY_MSR_SPEED100 ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
ruephy_status(struct mii_softc *phy)
{
	struct mii_data *mii = phy->mii_pdata;
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int bmsr, bmcr, msr;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	msr = PHY_READ(phy, RUEPHY_MII_MSR) | PHY_READ(phy, RUEPHY_MII_MSR);
	if (msr & RUEPHY_MSR_LINK)
		mii->mii_media_status |= IFM_ACTIVE;

	bmcr = PHY_READ(phy, MII_BMCR);
	if (bmcr & BMCR_ISO) {
		mii->mii_media_active |= IFM_NONE;
		mii->mii_media_status = 0;
		return;
	}

	bmsr = PHY_READ(phy, MII_BMSR) | PHY_READ(phy, MII_BMSR);
	if (bmcr & BMCR_AUTOEN) {
		if ((bmsr & BMSR_ACOMP) == 0) {
			/* Erg, still trying, I guess... */
			mii->mii_media_active |= IFM_NONE;
			return;
		}

		if (msr & RUEPHY_MSR_SPEED100)
			mii->mii_media_active |= IFM_100_TX;
		else
			mii->mii_media_active |= IFM_10_T;

		if (msr & RUEPHY_MSR_DUPLEX)
			mii->mii_media_active |=
			    IFM_FDX | mii_phy_flowstatus(phy);
		else
			mii->mii_media_active |= IFM_HDX;
	} else
		mii->mii_media_active = ife->ifm_media;
}