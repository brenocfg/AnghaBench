#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mii_softc {int mii_flags; int mii_extcapabilities; int mii_capabilities; TYPE_2__* mii_pdata; } ;
struct ifmedia_entry {int ifm_media; } ;
struct TYPE_3__ {struct ifmedia_entry* ifm_cur; } ;
struct TYPE_4__ {TYPE_1__ mii_media; } ;

/* Variables and functions */
 int ANAR_CSMA ; 
 int ANAR_FC ; 
 int ANAR_X_FD ; 
 int ANAR_X_HD ; 
 int ANAR_X_PAUSE_ASYM ; 
 int ANAR_X_PAUSE_TOWARDS ; 
 int BMCR_AUTOEN ; 
 int BMCR_STARTNEG ; 
 int BMSR_100TXFDX ; 
 int BMSR_10TFDX ; 
 int BMSR_MEDIA_TO_ANAR (int) ; 
 int EJUSTRETURN ; 
 int EXTSR_1000TFDX ; 
 int EXTSR_1000THDX ; 
 int EXTSR_1000XFDX ; 
 int EXTSR_1000XHDX ; 
 int GTCR_ADV_1000TFDX ; 
 int GTCR_ADV_1000THDX ; 
 int IFM_FLOW ; 
 int MIIF_FORCEPAUSE ; 
 int MIIF_HAVE_GTCR ; 
 int MIIF_IS_1000X ; 
 int /*<<< orphan*/  MII_100T2CR ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

int
mii_phy_auto(struct mii_softc *sc)
{
	struct ifmedia_entry *ife = sc->mii_pdata->mii_media.ifm_cur;
	int anar, gtcr;

	/*
	 * Check for 1000BASE-X.  Autonegotiation is a bit
	 * different on such devices.
	 */
	if ((sc->mii_flags & MIIF_IS_1000X) != 0) {
		anar = 0;
		if ((sc->mii_extcapabilities & EXTSR_1000XFDX) != 0)
			anar |= ANAR_X_FD;
		if ((sc->mii_extcapabilities & EXTSR_1000XHDX) != 0)
			anar |= ANAR_X_HD;

		if ((ife->ifm_media & IFM_FLOW) != 0 ||
		    (sc->mii_flags & MIIF_FORCEPAUSE) != 0)
			anar |= ANAR_X_PAUSE_TOWARDS;
		PHY_WRITE(sc, MII_ANAR, anar);
	} else {
		anar = BMSR_MEDIA_TO_ANAR(sc->mii_capabilities) |
		    ANAR_CSMA;
		if ((ife->ifm_media & IFM_FLOW) != 0 ||
		    (sc->mii_flags & MIIF_FORCEPAUSE) != 0) {
			if ((sc->mii_capabilities &
			    (BMSR_10TFDX | BMSR_100TXFDX)) != 0)
				anar |= ANAR_FC;
			/* XXX Only 1000BASE-T has PAUSE_ASYM? */
			if (((sc->mii_flags & MIIF_HAVE_GTCR) != 0) &&
			    (sc->mii_extcapabilities &
			    (EXTSR_1000THDX | EXTSR_1000TFDX)) != 0)
				anar |= ANAR_X_PAUSE_ASYM;
		}
		PHY_WRITE(sc, MII_ANAR, anar);
		if ((sc->mii_flags & MIIF_HAVE_GTCR) != 0) {
			gtcr = 0;
			if ((sc->mii_extcapabilities & EXTSR_1000TFDX) != 0)
				gtcr |= GTCR_ADV_1000TFDX;
			if ((sc->mii_extcapabilities & EXTSR_1000THDX) != 0)
				gtcr |= GTCR_ADV_1000THDX;
			PHY_WRITE(sc, MII_100T2CR, gtcr);
		}
	}
	PHY_WRITE(sc, MII_BMCR, BMCR_AUTOEN | BMCR_STARTNEG);
	return (EJUSTRETURN);
}