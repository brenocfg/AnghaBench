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
struct lpc32xx_pll_clk {int /*<<< orphan*/  reg; int /*<<< orphan*/  enable; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PLL_CTRL_LOCK ; 
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpc32xx_pll_clk* to_lpc32xx_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static int clk_pll_enable(struct clk_hw *hw)
{
	struct lpc32xx_pll_clk *clk = to_lpc32xx_pll_clk(hw);
	u32 val, count;

	regmap_update_bits(clk_regmap, clk->reg, clk->enable, clk->enable);

	for (count = 0; count < 1000; count++) {
		regmap_read(clk_regmap, clk->reg, &val);
		if (val & PLL_CTRL_LOCK)
			break;
	}

	if (val & PLL_CTRL_LOCK)
		return 0;

	return -ETIMEDOUT;
}