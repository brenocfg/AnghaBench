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
struct mii_softc {struct mii_data* mii_pdata; } ;
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_media_status; } ;

/* Variables and functions */
 int BMCR_AUTOEN ; 
 int BMSR_ACOMP ; 
 int BMSR_LINK ; 
 int IFM_1000_T ; 
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
 int /*<<< orphan*/  TRUEPHY_SR ; 
 int TRUEPHY_SR_FDX ; 
#define  TRUEPHY_SR_SPD_1000T 130 
#define  TRUEPHY_SR_SPD_100TX 129 
#define  TRUEPHY_SR_SPD_10T 128 
 int TRUEPHY_SR_SPD_MASK ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
truephy_status(struct mii_softc *sc)
{
	struct mii_data *mii = sc->mii_pdata;
	int bmsr, bmcr, sr;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	sr = PHY_READ(sc, TRUEPHY_SR);
	bmcr = PHY_READ(sc, MII_BMCR);

	bmsr = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
	if (bmsr & BMSR_LINK)
		mii->mii_media_status |= IFM_ACTIVE;

	if (bmcr & BMCR_AUTOEN) {
		if ((bmsr & BMSR_ACOMP) == 0) {
			mii->mii_media_active |= IFM_NONE;
			return;
		}
	}

	switch (sr & TRUEPHY_SR_SPD_MASK) {
	case TRUEPHY_SR_SPD_1000T:
		mii->mii_media_active |= IFM_1000_T;
		break;
	case TRUEPHY_SR_SPD_100TX:
		mii->mii_media_active |= IFM_100_TX;
		break;
	case TRUEPHY_SR_SPD_10T:
		mii->mii_media_active |= IFM_10_T;
		break;
	default:
		/* XXX will this ever happen? */
		printf("invalid media SR %#x\n", sr);
		mii->mii_media_active |= IFM_NONE;
		return;
	}

	if (sr & TRUEPHY_SR_FDX)
		mii->mii_media_active |= IFM_FDX | mii_phy_flowstatus(sc);
	else
		mii->mii_media_active |= IFM_HDX;
}