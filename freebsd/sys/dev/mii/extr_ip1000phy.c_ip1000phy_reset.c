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
struct mii_softc {int mii_flags; } ;

/* Variables and functions */
 int IP1000PHY_BMCR_AUTOEN ; 
 int IP1000PHY_BMCR_FDX ; 
 int /*<<< orphan*/  IP1000PHY_MII_BMCR ; 
 int MIIF_PHYPRIV0 ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip1000phy_load_dspcode (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_reset (struct mii_softc*) ; 

__attribute__((used)) static void
ip1000phy_reset(struct mii_softc *sc)
{
	uint32_t reg;

	mii_phy_reset(sc);

	/* clear autoneg/full-duplex as we don't want it after reset */
	reg = PHY_READ(sc, IP1000PHY_MII_BMCR);
	reg &= ~(IP1000PHY_BMCR_AUTOEN | IP1000PHY_BMCR_FDX);
	PHY_WRITE(sc, MII_BMCR, reg);

	if ((sc->mii_flags & MIIF_PHYPRIV0) != 0)
		ip1000phy_load_dspcode(sc);
}