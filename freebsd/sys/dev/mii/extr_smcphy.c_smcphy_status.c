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
typedef  int uint32_t ;
struct mii_softc {struct mii_data* mii_pdata; } ;
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_media_status; } ;

/* Variables and functions */
 int BMCR_AUTOEN ; 
 int BMCR_ISO ; 
 int BMCR_LOOP ; 
 int BMSR_ACOMP ; 
 int BMSR_LINK ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int IFM_LOOP ; 
 int IFM_NONE ; 
 int MII_BMCR ; 
 int MII_BMSR ; 
 int PHY_READ (struct mii_softc*,int) ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
smcphy_status(struct mii_softc *sc)
{
	struct mii_data *mii;
	uint32_t bmcr, bmsr, status;

	mii = sc->mii_pdata;
	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	bmsr = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
	if ((bmsr & BMSR_LINK) != 0)
		mii->mii_media_status |= IFM_ACTIVE;

	bmcr = PHY_READ(sc, MII_BMCR);
	if ((bmcr & BMCR_ISO) != 0) {
		mii->mii_media_active |= IFM_NONE;
		mii->mii_media_status = 0;
		return;
	}

	if ((bmcr & BMCR_LOOP) != 0)
		mii->mii_media_active |= IFM_LOOP;

	if ((bmcr & BMCR_AUTOEN) != 0) {
		if ((bmsr & BMSR_ACOMP) == 0) {
			/* Erg, still trying, I guess... */
			mii->mii_media_active |= IFM_NONE;
			return;
		}
	}

	status = PHY_READ(sc, 0x12);
	if (status & 0x0080)
		mii->mii_media_active |= IFM_100_TX;
	else
		mii->mii_media_active |= IFM_10_T;
	if (status & 0x0040)
		mii->mii_media_active |= IFM_FDX | mii_phy_flowstatus(sc);
	else
		mii->mii_media_active |= IFM_HDX;
}