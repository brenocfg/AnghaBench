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
struct padctl_softc {int dummy; } ;
struct padctl_lane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IOPHY_MISC_PAD_S0_CTL1_IDDQ ; 
 int /*<<< orphan*/  IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD ; 
 int /*<<< orphan*/  IOPHY_PLL_S0_CTL1_PLL1_MODE ; 
 int /*<<< orphan*/  IOPHY_PLL_S0_CTL1_PLL_IDDQ ; 
 int /*<<< orphan*/  IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD ; 
 int /*<<< orphan*/  IOPHY_PLL_S0_CTL1_PLL_RST_L ; 
 int /*<<< orphan*/  RD4 (struct padctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB3_PAD_MUX_SATA_IDDQ_DISABLE ; 
 int /*<<< orphan*/  WR4 (struct padctl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1 ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1 ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB3_PAD_MUX ; 

__attribute__((used)) static int
sata_powerdown(struct padctl_softc *sc, struct padctl_lane *lane)
{
	uint32_t reg;

	reg = RD4(sc, XUSB_PADCTL_USB3_PAD_MUX);
	reg &= ~USB3_PAD_MUX_SATA_IDDQ_DISABLE;
	WR4(sc, XUSB_PADCTL_USB3_PAD_MUX, reg);

	reg = RD4(sc, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	reg &= ~IOPHY_PLL_S0_CTL1_PLL_RST_L;
	WR4(sc, XUSB_PADCTL_IOPHY_PLL_S0_CTL1, reg);
	DELAY(100);

	reg = RD4(sc, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	reg &= ~IOPHY_PLL_S0_CTL1_PLL1_MODE;
	WR4(sc, XUSB_PADCTL_IOPHY_PLL_S0_CTL1, reg);
	DELAY(100);

	reg = RD4(sc, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	reg |= IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	reg |= IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	WR4(sc, XUSB_PADCTL_IOPHY_PLL_S0_CTL1, reg);
	DELAY(100);

	reg = RD4(sc, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	reg |= IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	reg |= IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	WR4(sc, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1, reg);
	DELAY(100);

	return (0);
}