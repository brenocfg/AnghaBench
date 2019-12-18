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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_ETH_CFG_SW_PHY_ADDR_SWAP ; 
 int /*<<< orphan*/  AR933X_ETH_CFG_SW_PHY_SWAP ; 
 int /*<<< orphan*/  ar933x_configure_gmac (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (char*,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void
ar933x_chip_init_gmac(void)
{
	int val;
	uint32_t gmac_cfg = 0;

	/*
	 * These two bits need a bit better explanation.
	 *
	 * The default configuration in the hardware is to map both
	 * ports to the internal switch.
	 *
	 * Here, GE0 == arge0, GE1 == arge1.
	 *
	 * The internal switch has:
	 * + 5 MAC ports, MAC0->MAC4.
	 * + 5 PHY ports, PHY0->PHY4,
	 * + MAC0 connects to GE1;
	 * + GE0 connects to PHY4;
	 * + The other mappings are MAC1->PHY0, MAC2->PHY1 .. MAC4->PHY3.
	 *
	 * The GE1 port is linked in via 1000MBit/full, supplying what is
	 * normally the 'WAN' switch ports.
	 *
	 * The switch is connected the MDIO bus on GE1.  It looks like
	 * a normal AR7240 on-board switch.
	 *
	 * The GE0 port is connected via MII to PHY4, and can operate in
	 * 10/100mbit, full/half duplex.  Ie, you can speak to PHY4 on
	 * the MDIO bus and everything will simply 'work'.
	 *
	 * So far so good.  This looks just like an AR7240 SoC.
	 *
	 * However, some configurations will just expose one or two
	 * physical ports.  In this case, some configuration bits can
	 * be set to tweak this.
	 *
	 * + CFG_SW_PHY_ADDR_SWAP swaps PHY port 0 with PHY port 4.
	 *   Ie, GE0's PHY shows up as PHY 0.  So if there's only
	 *   one physical port, there's no need to involve the
	 *   switch framework - it can just show up as a default,
	 *   normal single PHY.
	 *
	 * + CFG_SW_PHY_SWAP swaps the internal switch connection
	 *   between PHY0 and PHY4.  Ie, PHY4 connects to MAc1,
	 *   PHY0 connects to GE0.
	 */
	if ((resource_int_value("ar933x_gmac", 0, "override_phy", &val) == 0)
	    && (val == 0))
		return;
	if ((resource_int_value("ar933x_gmac", 0, "swap_phy", &val) == 0)
	    && (val == 1))
		gmac_cfg |= AR933X_ETH_CFG_SW_PHY_SWAP;
	if ((resource_int_value("ar933x_gmac", 0, "swap_phy_addr", &val) == 0)
	    && (val == 1))
		gmac_cfg |= AR933X_ETH_CFG_SW_PHY_ADDR_SWAP;
	ar933x_configure_gmac(gmac_cfg);
}