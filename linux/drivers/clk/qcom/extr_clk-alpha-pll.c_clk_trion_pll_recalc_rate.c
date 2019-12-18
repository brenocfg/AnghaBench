#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_REG_16BIT_WIDTH ; 
 int /*<<< orphan*/  PLL_ALPHA_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_L_VAL (struct clk_alpha_pll*) ; 
 unsigned long alpha_pll_calc_rate (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_trion_pll_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	struct regmap *regmap = pll->clkr.regmap;
	u32 l, frac;
	u64 prate = parent_rate;

	regmap_read(regmap, PLL_L_VAL(pll), &l);
	regmap_read(regmap, PLL_ALPHA_VAL(pll), &frac);

	return alpha_pll_calc_rate(prate, l, frac, ALPHA_REG_16BIT_WIDTH);
}