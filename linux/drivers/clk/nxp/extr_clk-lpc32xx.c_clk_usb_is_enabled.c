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
struct lpc32xx_usb_clk {int ctrl_mask; int ctrl_enable; int enable; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_CLKPWR_USB_CTRL ; 
 int /*<<< orphan*/  clk_regmap ; 
 int lpc32xx_usb_clk_read (struct lpc32xx_usb_clk*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct lpc32xx_usb_clk* to_lpc32xx_usb_clk (struct clk_hw*) ; 

__attribute__((used)) static int clk_usb_is_enabled(struct clk_hw *hw)
{
	struct lpc32xx_usb_clk *clk = to_lpc32xx_usb_clk(hw);
	u32 ctrl_val, val;

	if (clk->ctrl_mask) {
		regmap_read(clk_regmap, LPC32XX_CLKPWR_USB_CTRL, &ctrl_val);
		if ((ctrl_val & clk->ctrl_mask) != clk->ctrl_enable)
			return 0;
	}

	val = lpc32xx_usb_clk_read(clk);

	return ((val & clk->enable) == clk->enable);
}