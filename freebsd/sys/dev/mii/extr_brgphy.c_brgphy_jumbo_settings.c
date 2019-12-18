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
typedef  scalar_t__ u_long ;
struct mii_softc {scalar_t__ mii_mpd_model; } ;

/* Variables and functions */
 int BRGPHY_AUXCTL_LONG_PKT ; 
 int /*<<< orphan*/  BRGPHY_MII_AUXCTL ; 
 int /*<<< orphan*/  BRGPHY_MII_PHY_EXTCTL ; 
 int BRGPHY_PHY_EXTCTL_HIGH_LA ; 
 scalar_t__ ETHER_MAX_LEN ; 
 scalar_t__ MII_MODEL_BROADCOM_BCM5401 ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
brgphy_jumbo_settings(struct mii_softc *sc, u_long mtu)
{
	uint32_t	val;

	/* Set or clear jumbo frame settings in the PHY. */
	if (mtu > ETHER_MAX_LEN) {
		if (sc->mii_mpd_model == MII_MODEL_BROADCOM_BCM5401) {
			/* BCM5401 PHY cannot read-modify-write. */
			PHY_WRITE(sc, BRGPHY_MII_AUXCTL, 0x4c20);
		} else {
			PHY_WRITE(sc, BRGPHY_MII_AUXCTL, 0x7);
			val = PHY_READ(sc, BRGPHY_MII_AUXCTL);
			PHY_WRITE(sc, BRGPHY_MII_AUXCTL,
			    val | BRGPHY_AUXCTL_LONG_PKT);
		}

		val = PHY_READ(sc, BRGPHY_MII_PHY_EXTCTL);
		PHY_WRITE(sc, BRGPHY_MII_PHY_EXTCTL,
		    val | BRGPHY_PHY_EXTCTL_HIGH_LA);
	} else {
		PHY_WRITE(sc, BRGPHY_MII_AUXCTL, 0x7);
		val = PHY_READ(sc, BRGPHY_MII_AUXCTL);
		PHY_WRITE(sc, BRGPHY_MII_AUXCTL,
		    val & ~(BRGPHY_AUXCTL_LONG_PKT | 0x7));

		val = PHY_READ(sc, BRGPHY_MII_PHY_EXTCTL);
		PHY_WRITE(sc, BRGPHY_MII_PHY_EXTCTL,
			val & ~BRGPHY_PHY_EXTCTL_HIGH_LA);
	}
}