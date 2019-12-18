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
struct mii_softc {scalar_t__ mii_mpd_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZ8081_PHYCTL2 ; 
 scalar_t__ MII_MODEL_MICREL_KSZ8081 ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_phy_reset (struct mii_softc*) ; 

__attribute__((used)) static void
micphy_reset(struct mii_softc *sc)
{
	int reg;

	/*
	 * The 8081 has no "sticky bits" that survive a soft reset; several bits
	 * in the Phy Control Register 2 must be preserved across the reset.
	 * These bits are set up by the bootloader; they control how the phy
	 * interfaces to the board (such as clock frequency and LED behavior).
	 */
	if (sc->mii_mpd_model == MII_MODEL_MICREL_KSZ8081)
		reg = PHY_READ(sc, MII_KSZ8081_PHYCTL2);
	mii_phy_reset(sc);
	if (sc->mii_mpd_model == MII_MODEL_MICREL_KSZ8081)
		PHY_WRITE(sc, MII_KSZ8081_PHYCTL2, reg);
}