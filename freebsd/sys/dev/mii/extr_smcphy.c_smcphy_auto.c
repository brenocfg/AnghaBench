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
struct mii_softc {int mii_flags; int /*<<< orphan*/  mii_capabilities; } ;

/* Variables and functions */
 int ANAR_CSMA ; 
 int ANAR_FC ; 
 int BMCR_AUTOEN ; 
 int BMCR_STARTNEG ; 
 int BMSR_MEDIA_TO_ANAR (int /*<<< orphan*/ ) ; 
 int IFM_FLOW ; 
 int MIIF_FORCEPAUSE ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
smcphy_auto(struct mii_softc *sc, int media)
{
	uint16_t	anar;

	anar = BMSR_MEDIA_TO_ANAR(sc->mii_capabilities) | ANAR_CSMA;
	if ((media & IFM_FLOW) != 0 || (sc->mii_flags & MIIF_FORCEPAUSE) != 0)
		anar |= ANAR_FC;
	PHY_WRITE(sc, MII_ANAR, anar);
	/* Apparently this helps. */
	anar = PHY_READ(sc, MII_ANAR);
	PHY_WRITE(sc, MII_BMCR, BMCR_AUTOEN | BMCR_STARTNEG);
}