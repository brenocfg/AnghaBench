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
typedef  int uint16_t ;
struct mii_softc {int mii_flags; int mii_extcapabilities; scalar_t__ mii_mpd_model; int /*<<< orphan*/  mii_capabilities; } ;

/* Variables and functions */
 int ANAR_CSMA ; 
 int ANAR_PAUSE_TOWARDS ; 
 int BMCR_AUTOEN ; 
 int BMCR_RESET ; 
 int BMCR_STARTNEG ; 
 int BMSR_MEDIA_TO_ANAR (int /*<<< orphan*/ ) ; 
 int EJUSTRETURN ; 
 int EXTSR_1000TFDX ; 
 int EXTSR_1000THDX ; 
 int GTCR_ADV_1000TFDX ; 
 int GTCR_ADV_1000THDX ; 
 scalar_t__ IFM_AUTO ; 
 int IFM_FDX ; 
 int IFM_FLOW ; 
 scalar_t__ IFM_SUBTYPE (int) ; 
 int MIIF_FORCEPAUSE ; 
 int /*<<< orphan*/  MII_100T2CR ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ MII_MODEL_xxATHEROS_F1 ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
atphy_setmedia(struct mii_softc *sc, int media)
{
	uint16_t anar;

	anar = BMSR_MEDIA_TO_ANAR(sc->mii_capabilities) | ANAR_CSMA;
	if ((IFM_SUBTYPE(media) == IFM_AUTO || (media & IFM_FDX) != 0) &&
	    ((media & IFM_FLOW) != 0 ||
	    (sc->mii_flags & MIIF_FORCEPAUSE) != 0))
		anar |= ANAR_PAUSE_TOWARDS;
	PHY_WRITE(sc, MII_ANAR, anar);
	if ((sc->mii_extcapabilities &
	     (EXTSR_1000TFDX | EXTSR_1000THDX)) != 0)
		PHY_WRITE(sc, MII_100T2CR, GTCR_ADV_1000TFDX |
		    GTCR_ADV_1000THDX);
	else if (sc->mii_mpd_model == MII_MODEL_xxATHEROS_F1) {
		/*
		 * AR8132 has 10/100 PHY and the PHY uses the same
		 * model number of F1 gigabit PHY.  The PHY has no
		 * ability to establish gigabit link so explicitly
		 * disable 1000baseT configuration for the PHY.
		 * Otherwise, there is a case that atphy(4) could
		 * not establish a link against gigabit link partner
		 * unless the link partner supports down-shifting.
		 */
		PHY_WRITE(sc, MII_100T2CR, 0);
	}
	PHY_WRITE(sc, MII_BMCR, BMCR_RESET | BMCR_AUTOEN | BMCR_STARTNEG);

	return (EJUSTRETURN);
}