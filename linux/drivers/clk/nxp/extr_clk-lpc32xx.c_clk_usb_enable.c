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
typedef  int u32 ;
struct lpc32xx_usb_clk {int enable; int busy; scalar_t__ ctrl_mask; int /*<<< orphan*/  ctrl_enable; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LPC32XX_CLKPWR_USB_CTRL ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_regmap ; 
 int lpc32xx_usb_clk_read (struct lpc32xx_usb_clk*) ; 
 int /*<<< orphan*/  lpc32xx_usb_clk_write (struct lpc32xx_usb_clk*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lpc32xx_usb_clk* to_lpc32xx_usb_clk (struct clk_hw*) ; 

__attribute__((used)) static int clk_usb_enable(struct clk_hw *hw)
{
	struct lpc32xx_usb_clk *clk = to_lpc32xx_usb_clk(hw);
	u32 val, ctrl_val, count;

	pr_debug("%s: 0x%x\n", clk_hw_get_name(hw), clk->enable);

	if (clk->ctrl_mask) {
		regmap_read(clk_regmap, LPC32XX_CLKPWR_USB_CTRL, &ctrl_val);
		regmap_update_bits(clk_regmap, LPC32XX_CLKPWR_USB_CTRL,
				   clk->ctrl_mask, clk->ctrl_enable);
	}

	val = lpc32xx_usb_clk_read(clk);
	if (clk->busy && (val & clk->busy) == clk->busy) {
		if (clk->ctrl_mask)
			regmap_write(clk_regmap, LPC32XX_CLKPWR_USB_CTRL,
				     ctrl_val);
		return -EBUSY;
	}

	val |= clk->enable;
	lpc32xx_usb_clk_write(clk, val);

	for (count = 0; count < 1000; count++) {
		val = lpc32xx_usb_clk_read(clk);
		if ((val & clk->enable) == clk->enable)
			break;
	}

	if ((val & clk->enable) == clk->enable)
		return 0;

	if (clk->ctrl_mask)
		regmap_write(clk_regmap, LPC32XX_CLKPWR_USB_CTRL, ctrl_val);

	return -ETIMEDOUT;
}