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
struct mii_data {int dummy; } ;

/* Variables and functions */
 int BMCR_ISO ; 
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
acphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	int reg;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		/* Wake & deisolate up if necessary */
		reg = PHY_READ(sc, MII_BMCR);
		if (reg & (BMCR_ISO | BMCR_PDOWN))
			PHY_WRITE(sc, MII_BMCR, reg & ~(BMCR_ISO | BMCR_PDOWN));

		mii_phy_setmedia(sc);
		break;

	case MII_TICK:
		/*
		 * This PHY's autonegotiation doesn't need to be kicked.
		 */
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}