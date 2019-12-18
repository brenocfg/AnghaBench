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
struct mii_softc {int mii_mpd_model; } ;

/* Variables and functions */
 int BMCR_FDX ; 
 int BMCR_S100 ; 
 int BMCR_STARTNEG ; 
 int ECR2_100AUTOPWRDN ; 
 int ECR2_10AUTOPWRDN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_ICSPHY_ECR2 ; 
#define  MII_MODEL_ICS_1890 130 
#define  MII_MODEL_ICS_1892 129 
#define  MII_MODEL_ICS_1893 128 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_phy_reset (struct mii_softc*) ; 

__attribute__((used)) static void
icsphy_reset(struct mii_softc *sc)
{

	mii_phy_reset(sc);
	/* set powerdown feature */
	switch (sc->mii_mpd_model) {
		case MII_MODEL_ICS_1890:
		case MII_MODEL_ICS_1893:
			PHY_WRITE(sc, MII_ICSPHY_ECR2, ECR2_100AUTOPWRDN);
			break;
		case MII_MODEL_ICS_1892:
			PHY_WRITE(sc, MII_ICSPHY_ECR2,
			    ECR2_10AUTOPWRDN|ECR2_100AUTOPWRDN);
			break;
		default:
			/* 1889 have no ECR2 */
			break;
	}
	/*
	 * There is no description that the reset do auto-negotiation in the
	 * data sheet.
	 */
	PHY_WRITE(sc, MII_BMCR, BMCR_S100|BMCR_STARTNEG|BMCR_FDX);
}