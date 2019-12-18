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
struct tlphy_softc {int /*<<< orphan*/  sc_mii; scalar_t__ sc_need_acomp; } ;

/* Variables and functions */
 int ANAR_10_FD ; 
 int ANER_LPAN ; 
 int /*<<< orphan*/  BMCR_FDX ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_ANER ; 
 int /*<<< orphan*/  MII_ANLPAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tlphy_acomp(struct tlphy_softc *sc)
{
	int aner, anlpar;

	sc->sc_need_acomp = 0;

	/*
	 * Grr, braindead ThunderLAN PHY doesn't self-configure
	 * after autonegotiation.  We have to do it ourselves
	 * based on the link partner status.
	 */

	aner = PHY_READ(&sc->sc_mii, MII_ANER);
	if (aner & ANER_LPAN) {
		anlpar = PHY_READ(&sc->sc_mii, MII_ANLPAR) &
		    PHY_READ(&sc->sc_mii, MII_ANAR);
		if (anlpar & ANAR_10_FD) {
			PHY_WRITE(&sc->sc_mii, MII_BMCR, BMCR_FDX);
			return;
		}
	}
	PHY_WRITE(&sc->sc_mii, MII_BMCR, 0);
}