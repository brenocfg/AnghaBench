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
struct mii_softc {scalar_t__ mii_mpd_model; scalar_t__ mii_mpd_rev; int /*<<< orphan*/  mii_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ MII_MODEL_REALTEK_RTL8251 ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RGEPHY_8211B ; 
 int /*<<< orphan*/  RGEPHY_BMCR_PDOWN ; 
 int RGEPHY_BMSR_LINK ; 
 int /*<<< orphan*/  RGEPHY_MII_BMCR ; 
 int /*<<< orphan*/  RGEPHY_MII_BMSR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
rgephy_loop(struct mii_softc *sc)
{
	int i;

	if (sc->mii_mpd_model != MII_MODEL_REALTEK_RTL8251 &&
	    sc->mii_mpd_rev < RGEPHY_8211B) {
		PHY_WRITE(sc, RGEPHY_MII_BMCR, RGEPHY_BMCR_PDOWN);
		DELAY(1000);
	}

	for (i = 0; i < 15000; i++) {
		if (!(PHY_READ(sc, RGEPHY_MII_BMSR) & RGEPHY_BMSR_LINK)) {
#if 0
			device_printf(sc->mii_dev, "looped %d\n", i);
#endif
			break;
		}
		DELAY(10);
	}
}