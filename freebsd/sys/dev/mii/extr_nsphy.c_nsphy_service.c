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
 int /*<<< orphan*/  EJUSTRETURN ; 
#define  MII_MEDIACHG 130 
 int /*<<< orphan*/  MII_NSPHY_PCR ; 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PCR_CIMDIS ; 
 int PCR_FLINK100 ; 
 int PCR_LED4MODE ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_phy_mac_match (struct mii_softc*,char*) ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_tick (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
nsphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	int reg;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		reg = PHY_READ(sc, MII_NSPHY_PCR);

		/*
		 * Set up the PCR to use LED4 to indicate full-duplex
		 * in both 10baseT and 100baseTX modes.
		 */
		reg |= PCR_LED4MODE;

		/*
		 * Make sure Carrier Integrity Monitor function is
		 * disabled (normal for Node operation, but sometimes
		 * it's not set?!)
		 */
		reg |= PCR_CIMDIS;

		/*
		 * Make sure "force link good" is set to normal mode.
		 * It's only intended for debugging.
		 */
		reg |= PCR_FLINK100;

		/*
		 * Mystery bits which are supposedly `reserved',
		 * but we seem to need to set them when the PHY
		 * is connected to some interfaces:
		 *
		 * 0x0400 is needed for fxp
		 *        (Intel EtherExpress Pro 10+/100B, 82557 chip)
		 *        (nsphy with a DP83840 chip)
		 * 0x0100 may be needed for some other card
		 */
		reg |= 0x0100 | 0x0400;

		if (mii_phy_mac_match(sc, "fxp"))
			PHY_WRITE(sc, MII_NSPHY_PCR, reg);

		mii_phy_setmedia(sc);
		break;

	case MII_TICK:
		if (mii_phy_tick(sc) == EJUSTRETURN)
			return (0);
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}