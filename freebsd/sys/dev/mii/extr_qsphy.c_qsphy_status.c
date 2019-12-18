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
 int BMCR_ISO ; 
 int BMCR_LOOP ; 
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
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_QSPHY_PCTL ; 
#define  PCTL_100_T4 133 
#define  PCTL_100_TX 132 
#define  PCTL_100_TX_FDX 131 
#define  PCTL_10_T 130 
#define  PCTL_10_T_FDX 129 
#define  PCTL_AN 128 
 int PCTL_OPMASK ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
qsphy_status(struct mii_softc *sc)
{
	struct mii_data *mii = sc->mii_pdata;
	int bmsr, bmcr, pctl;

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

	pctl = PHY_READ(sc, MII_QSPHY_PCTL);
	switch (pctl & PCTL_OPMASK) {
	case PCTL_10_T:
		mii->mii_media_active |= IFM_10_T|IFM_HDX;
		break;
	case PCTL_10_T_FDX:
		mii->mii_media_active |= IFM_10_T|IFM_FDX;
		break;
	case PCTL_100_TX:
		mii->mii_media_active |= IFM_100_TX|IFM_HDX;
		break;
	case PCTL_100_TX_FDX:
		mii->mii_media_active |= IFM_100_TX|IFM_FDX;
		break;
	case PCTL_100_T4:
		mii->mii_media_active |= IFM_100_T4|IFM_HDX;
		break;
	case PCTL_AN:
		mii->mii_media_active |= IFM_NONE;
		break;
	default:
		/* Erg... this shouldn't happen. */
		mii->mii_media_active |= IFM_NONE;
		break;
	}
	if ((mii->mii_media_active & IFM_FDX) != 0)
		mii->mii_media_active |= mii_phy_flowstatus(sc);
}