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
struct lpc32xx_clk {int busy_mask; int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lpc32xx_clk* to_lpc32xx_clk (struct clk_hw*) ; 

__attribute__((used)) static int clk_ddram_enable(struct clk_hw *hw)
{
	struct lpc32xx_clk *clk = to_lpc32xx_clk(hw);
	u32 val, hclk_div;

	regmap_read(clk_regmap, clk->reg, &val);
	hclk_div = val & clk->busy_mask;

	/*
	 * DDRAM clock must be 2 times higher than HCLK,
	 * this implies DDRAM clock can not be enabled,
	 * if HCLK clock rate is equal to ARM clock rate
	 */
	if (hclk_div == 0x0 || hclk_div == (BIT(1) | BIT(0)))
		return -EINVAL;

	return regmap_update_bits(clk_regmap, clk->reg,
				  clk->enable_mask, hclk_div << 7);
}