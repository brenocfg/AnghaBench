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
typedef  int u_int16_t ;
struct mii_softc {scalar_t__ mii_mpd_model; } ;

/* Variables and functions */
 int MII_BMTPHY_AUX2 ; 
 int MII_BMTPHY_INTR ; 
 scalar_t__ MII_MODEL_xxBROADCOM_BCM5221 ; 
 int PHY_READ (struct mii_softc*,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int,int) ; 
 int /*<<< orphan*/  mii_phy_reset (struct mii_softc*) ; 

__attribute__((used)) static void
bmtphy_reset(struct mii_softc *sc)
{
	u_int16_t data;

	mii_phy_reset(sc);

	if (sc->mii_mpd_model == MII_MODEL_xxBROADCOM_BCM5221) {
		/* Enable shadow register mode. */
		data = PHY_READ(sc, 0x1f);
		PHY_WRITE(sc, 0x1f, data | 0x0080);

		/* Enable APD (Auto PowerDetect). */
		data = PHY_READ(sc, MII_BMTPHY_AUX2);
		PHY_WRITE(sc, MII_BMTPHY_AUX2, data | 0x0020);

		/* Enable clocks across APD for Auto-MDIX functionality. */
		data = PHY_READ(sc, MII_BMTPHY_INTR);
		PHY_WRITE(sc, MII_BMTPHY_INTR, data | 0x0004);

		/* Disable shadow register mode. */
		data = PHY_READ(sc, 0x1f);
		PHY_WRITE(sc, 0x1f, data & ~0x0080);
	}
}