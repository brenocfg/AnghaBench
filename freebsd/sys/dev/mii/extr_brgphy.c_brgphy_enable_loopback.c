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
struct mii_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRGPHY_BMCR_LOOP ; 
 int BRGPHY_BMSR_LINK ; 
 int /*<<< orphan*/  BRGPHY_MII_BMCR ; 
 int /*<<< orphan*/  BRGPHY_MII_BMSR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brgphy_enable_loopback(struct mii_softc *sc)
{
	int i;

	PHY_WRITE(sc, BRGPHY_MII_BMCR, BRGPHY_BMCR_LOOP);
	for (i = 0; i < 15000; i++) {
		if (!(PHY_READ(sc, BRGPHY_MII_BMSR) & BRGPHY_BMSR_LINK))
			break;
		DELAY(10);
	}
}