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
struct mii_softc {int mii_flags; int /*<<< orphan*/  mii_capabilities; } ;

/* Variables and functions */
 int ANAR_CSMA ; 
 int BMSR_MEDIA_TO_ANAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EJUSTRETURN ; 
 int IFM_FLOW ; 
 int MIIF_FORCEPAUSE ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int RGEPHY_1000CTL_AFD ; 
 int RGEPHY_1000CTL_AHD ; 
 int RGEPHY_ANAR_ASP ; 
 int RGEPHY_ANAR_PC ; 
 int RGEPHY_BMCR_AUTOEN ; 
 int RGEPHY_BMCR_STARTNEG ; 
 int /*<<< orphan*/  RGEPHY_MII_1000CTL ; 
 int /*<<< orphan*/  RGEPHY_MII_ANAR ; 
 int /*<<< orphan*/  RGEPHY_MII_BMCR ; 
 int /*<<< orphan*/  rgephy_loop (struct mii_softc*) ; 

__attribute__((used)) static int
rgephy_mii_phy_auto(struct mii_softc *sc, int media)
{
	int anar;

	rgephy_loop(sc);
	PHY_RESET(sc);

	anar = BMSR_MEDIA_TO_ANAR(sc->mii_capabilities) | ANAR_CSMA;
	if ((media & IFM_FLOW) != 0 || (sc->mii_flags & MIIF_FORCEPAUSE) != 0)
		anar |= RGEPHY_ANAR_PC | RGEPHY_ANAR_ASP;
	PHY_WRITE(sc, RGEPHY_MII_ANAR, anar);
	DELAY(1000);
	PHY_WRITE(sc, RGEPHY_MII_1000CTL,
	    RGEPHY_1000CTL_AHD | RGEPHY_1000CTL_AFD);
	DELAY(1000);
	PHY_WRITE(sc, RGEPHY_MII_BMCR,
	    RGEPHY_BMCR_AUTOEN | RGEPHY_BMCR_STARTNEG);
	DELAY(100);

	return (EJUSTRETURN);
}