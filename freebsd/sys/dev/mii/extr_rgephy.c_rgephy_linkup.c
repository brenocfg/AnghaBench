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
struct mii_softc {int mii_flags; scalar_t__ mii_mpd_rev; } ;

/* Variables and functions */
 int MIIF_PHYPRIV0 ; 
 int MIIF_PHYPRIV1 ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ RGEPHY_8211B ; 
 scalar_t__ RGEPHY_8211F ; 
 int /*<<< orphan*/  RGEPHY_F_MII_SSR ; 
 int RGEPHY_F_SSR_LINK ; 
 int /*<<< orphan*/  RGEPHY_MII_SSR ; 
 int RGEPHY_SSR_LINK ; 
 int /*<<< orphan*/  RL_GMEDIASTAT ; 
 int RL_GMEDIASTAT_LINK ; 
 int /*<<< orphan*/  URE_GMEDIASTAT ; 

__attribute__((used)) static int
rgephy_linkup(struct mii_softc *sc)
{
	int linkup;
	uint16_t reg;

	linkup = 0;
	if ((sc->mii_flags & MIIF_PHYPRIV0) == 0 &&
	    sc->mii_mpd_rev >= RGEPHY_8211B) {
		if (sc->mii_mpd_rev == RGEPHY_8211F) {
			reg = PHY_READ(sc, RGEPHY_F_MII_SSR);
			if (reg & RGEPHY_F_SSR_LINK)
				linkup++;
		} else {
			reg = PHY_READ(sc, RGEPHY_MII_SSR);
			if (reg & RGEPHY_SSR_LINK)
				linkup++;
		}
	} else {
		if (sc->mii_flags & MIIF_PHYPRIV1)
			reg = PHY_READ(sc, URE_GMEDIASTAT);
		else
			reg = PHY_READ(sc, RL_GMEDIASTAT);
		if (reg & RL_GMEDIASTAT_LINK)
			linkup++;
	}

	return (linkup);
}