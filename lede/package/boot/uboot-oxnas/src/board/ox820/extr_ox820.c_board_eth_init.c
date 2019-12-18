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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  bd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_BASE ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  PINMUX_BANK_MFA ; 
 int /*<<< orphan*/  PINMUX_MACA_MDC ; 
 int /*<<< orphan*/  PINMUX_MACA_MDIO ; 
 int /*<<< orphan*/  SYS_CTRL_CLK_MAC ; 
 int /*<<< orphan*/  SYS_CTRL_GMAC_AUTOSPEED ; 
 int /*<<< orphan*/  SYS_CTRL_GMAC_CKEN_GTX ; 
 int /*<<< orphan*/  SYS_CTRL_GMAC_CTRL ; 
 int /*<<< orphan*/  SYS_CTRL_GMAC_SIMPLE_MUX ; 
 int /*<<< orphan*/  SYS_CTRL_RST_MAC ; 
 int designware_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinmux_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_block (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int board_eth_init(bd_t *bis)
{
	u32 value;

	/* set the pin multiplexers to enable talking to Ethernent Phys */
	pinmux_set(PINMUX_BANK_MFA, 3, PINMUX_MACA_MDC);
	pinmux_set(PINMUX_BANK_MFA, 4, PINMUX_MACA_MDIO);

	// Ensure the MAC block is properly reset
	reset_block(SYS_CTRL_RST_MAC, 1);
	udelay(10);
	reset_block(SYS_CTRL_RST_MAC, 0);

	// Enable the clock to the MAC block
	enable_clock(SYS_CTRL_CLK_MAC);

	value = readl(SYS_CTRL_GMAC_CTRL);
	/* Use simple mux for 25/125 Mhz clock switching */
	value |= BIT(SYS_CTRL_GMAC_SIMPLE_MUX);
	/* Enable GMII_GTXCLK to follow GMII_REFCLK - required for gigabit PHY */
	value |= BIT(SYS_CTRL_GMAC_CKEN_GTX);
	/* set auto tx speed */
	value |= BIT(SYS_CTRL_GMAC_AUTOSPEED);

	writel(value, SYS_CTRL_GMAC_CTRL);

	return designware_initialize(MAC_BASE, PHY_INTERFACE_MODE_RGMII);
}