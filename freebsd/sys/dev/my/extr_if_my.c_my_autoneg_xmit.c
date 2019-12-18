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
struct my_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int /*<<< orphan*/  PHY_BMCR ; 
 int PHY_BMCR_AUTONEGENBL ; 
 int PHY_BMCR_AUTONEGRSTR ; 
 int PHY_BMCR_RESET ; 
 int my_phy_readreg (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_phy_writereg (struct my_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
my_autoneg_xmit(struct my_softc * sc)
{
	u_int16_t       phy_sts = 0;

	MY_LOCK_ASSERT(sc);

	my_phy_writereg(sc, PHY_BMCR, PHY_BMCR_RESET);
	DELAY(500);
	while (my_phy_readreg(sc, PHY_BMCR) & PHY_BMCR_RESET);

	phy_sts = my_phy_readreg(sc, PHY_BMCR);
	phy_sts |= PHY_BMCR_AUTONEGENBL | PHY_BMCR_AUTONEGRSTR;
	my_phy_writereg(sc, PHY_BMCR, phy_sts);

	return;
}