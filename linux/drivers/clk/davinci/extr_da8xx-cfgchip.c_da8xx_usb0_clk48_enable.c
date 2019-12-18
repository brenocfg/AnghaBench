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
struct da8xx_usb0_clk48 {int /*<<< orphan*/  fck; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 unsigned int CFGCHIP2_PHYCLKGD ; 
 unsigned int CFGCHIP2_PHYPWRDN ; 
 unsigned int CFGCHIP2_PHY_PLLON ; 
 unsigned int CFGCHIP2_RESET ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct da8xx_usb0_clk48* to_da8xx_usb0_clk48 (struct clk_hw*) ; 

__attribute__((used)) static int da8xx_usb0_clk48_enable(struct clk_hw *hw)
{
	struct da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	unsigned int mask, val;
	int ret;

	/* Locking the USB 2.O PLL requires that the USB 2.O PSC is enabled
	 * temporaily. It can be turned back off once the PLL is locked.
	 */
	clk_enable(usb0->fck);

	/* Turn on the USB 2.0 PHY, but just the PLL, and not OTG. The USB 1.1
	 * PHY may use the USB 2.0 PLL clock without USB 2.0 OTG being used.
	 */
	mask = CFGCHIP2_RESET | CFGCHIP2_PHYPWRDN | CFGCHIP2_PHY_PLLON;
	val = CFGCHIP2_PHY_PLLON;

	regmap_write_bits(usb0->regmap, CFGCHIP(2), mask, val);
	ret = regmap_read_poll_timeout(usb0->regmap, CFGCHIP(2), val,
				       val & CFGCHIP2_PHYCLKGD, 0, 500000);

	clk_disable(usb0->fck);

	return ret;
}