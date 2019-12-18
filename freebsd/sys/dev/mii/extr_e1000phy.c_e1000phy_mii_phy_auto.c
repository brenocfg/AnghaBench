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
struct mii_softc {int mii_flags; int mii_extcapabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_1GCR ; 
 int E1000_1GCR_1000T ; 
 int E1000_1GCR_1000T_FD ; 
 int /*<<< orphan*/  E1000_AR ; 
 int E1000_AR_100TX ; 
 int E1000_AR_100TX_FD ; 
 int E1000_AR_10T ; 
 int E1000_AR_10T_FD ; 
 int E1000_AR_ASM_DIR ; 
 int E1000_AR_PAUSE ; 
 int E1000_AR_SELECTOR_FIELD ; 
 int /*<<< orphan*/  E1000_CR ; 
 int E1000_CR_AUTO_NEG_ENABLE ; 
 int E1000_CR_RESTART_AUTO_NEG ; 
 int E1000_FA_1000X ; 
 int E1000_FA_1000X_FD ; 
 int EJUSTRETURN ; 
 int EXTSR_1000TFDX ; 
 int EXTSR_1000THDX ; 
 int IFM_FLOW ; 
 int MIIF_FORCEPAUSE ; 
 int MIIF_HAVEFIBER ; 
 int MIIF_HAVE_GTCR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
e1000phy_mii_phy_auto(struct mii_softc *sc, int media)
{
	uint16_t reg;

	if ((sc->mii_flags & MIIF_HAVEFIBER) == 0) {
		reg = PHY_READ(sc, E1000_AR);
		reg &= ~(E1000_AR_PAUSE | E1000_AR_ASM_DIR);
		reg |= E1000_AR_10T | E1000_AR_10T_FD |
		    E1000_AR_100TX | E1000_AR_100TX_FD;
		if ((media & IFM_FLOW) != 0 ||
		    (sc->mii_flags & MIIF_FORCEPAUSE) != 0)
			reg |= E1000_AR_PAUSE | E1000_AR_ASM_DIR;
		PHY_WRITE(sc, E1000_AR, reg | E1000_AR_SELECTOR_FIELD);
	} else
		PHY_WRITE(sc, E1000_AR, E1000_FA_1000X_FD | E1000_FA_1000X);
	if ((sc->mii_flags & MIIF_HAVE_GTCR) != 0) {
		reg = 0;
		if ((sc->mii_extcapabilities & EXTSR_1000TFDX) != 0)
			reg |= E1000_1GCR_1000T_FD;
		if ((sc->mii_extcapabilities & EXTSR_1000THDX) != 0)
			reg |= E1000_1GCR_1000T;
		PHY_WRITE(sc, E1000_1GCR, reg);
	}
	PHY_WRITE(sc, E1000_CR,
	    E1000_CR_AUTO_NEG_ENABLE | E1000_CR_RESTART_AUTO_NEG);

	return (EJUSTRETURN);
}