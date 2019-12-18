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
struct mii_softc {scalar_t__ mii_mpd_model; int mii_flags; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int IFM_FLOW ; 
 int IP1000PHY_1000CR_1000T ; 
 int IP1000PHY_1000CR_1000T_FDX ; 
 int IP1000PHY_1000CR_MASTER ; 
 int IP1000PHY_ANAR_100TX ; 
 int IP1000PHY_ANAR_100TX_FDX ; 
 int IP1000PHY_ANAR_10T ; 
 int IP1000PHY_ANAR_10T_FDX ; 
 int IP1000PHY_ANAR_APAUSE ; 
 int IP1000PHY_ANAR_CSMA ; 
 int IP1000PHY_ANAR_NP ; 
 int IP1000PHY_ANAR_PAUSE ; 
 int IP1000PHY_BMCR_AUTOEN ; 
 int IP1000PHY_BMCR_FDX ; 
 int IP1000PHY_BMCR_STARTNEG ; 
 int /*<<< orphan*/  IP1000PHY_MII_1000CR ; 
 int /*<<< orphan*/  IP1000PHY_MII_ANAR ; 
 int /*<<< orphan*/  IP1000PHY_MII_BMCR ; 
 int MIIF_FORCEPAUSE ; 
 scalar_t__ MII_MODEL_xxICPLUS_IP1001 ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ip1000phy_mii_phy_auto(struct mii_softc *sc, int media)
{
	uint32_t reg;

	reg = 0;
	if (sc->mii_mpd_model == MII_MODEL_xxICPLUS_IP1001) {
		reg = PHY_READ(sc, IP1000PHY_MII_ANAR);
		reg &= ~(IP1000PHY_ANAR_PAUSE | IP1000PHY_ANAR_APAUSE);
		reg |= IP1000PHY_ANAR_NP;
	}
	reg |= IP1000PHY_ANAR_10T | IP1000PHY_ANAR_10T_FDX |
	    IP1000PHY_ANAR_100TX | IP1000PHY_ANAR_100TX_FDX;
	if ((media & IFM_FLOW) != 0 || (sc->mii_flags & MIIF_FORCEPAUSE) != 0)
		reg |= IP1000PHY_ANAR_PAUSE | IP1000PHY_ANAR_APAUSE;
	PHY_WRITE(sc, IP1000PHY_MII_ANAR, reg | IP1000PHY_ANAR_CSMA);

	reg = IP1000PHY_1000CR_1000T | IP1000PHY_1000CR_1000T_FDX;
	if (sc->mii_mpd_model != MII_MODEL_xxICPLUS_IP1001)
		reg |= IP1000PHY_1000CR_MASTER;
	PHY_WRITE(sc, IP1000PHY_MII_1000CR, reg);
	PHY_WRITE(sc, IP1000PHY_MII_BMCR, (IP1000PHY_BMCR_FDX |
	    IP1000PHY_BMCR_AUTOEN | IP1000PHY_BMCR_STARTNEG));

	return (EJUSTRETURN);
}