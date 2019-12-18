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
typedef  int u64 ;
struct pistachio_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CTRL1 ; 
 int PLL_CTRL1_FBDIV_MASK ; 
 int PLL_CTRL1_FBDIV_SHIFT ; 
 int PLL_CTRL1_REFDIV_MASK ; 
 int PLL_CTRL1_REFDIV_SHIFT ; 
 int /*<<< orphan*/  PLL_CTRL2 ; 
 int PLL_FRAC_CTRL2_FRAC_MASK ; 
 int PLL_FRAC_CTRL2_FRAC_SHIFT ; 
 int PLL_FRAC_CTRL2_POSTDIV1_MASK ; 
 int PLL_FRAC_CTRL2_POSTDIV1_SHIFT ; 
 int PLL_FRAC_CTRL2_POSTDIV2_MASK ; 
 int PLL_FRAC_CTRL2_POSTDIV2_SHIFT ; 
 scalar_t__ PLL_MODE_FRAC ; 
 int do_div_round_closest (int,int) ; 
 scalar_t__ pll_frac_get_mode (struct clk_hw*) ; 
 int pll_readl (struct pistachio_clk_pll*,int /*<<< orphan*/ ) ; 
 struct pistachio_clk_pll* to_pistachio_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long pll_gf40lp_frac_recalc_rate(struct clk_hw *hw,
						 unsigned long parent_rate)
{
	struct pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u64 val, prediv, fbdiv, frac, postdiv1, postdiv2, rate;

	val = pll_readl(pll, PLL_CTRL1);
	prediv = (val >> PLL_CTRL1_REFDIV_SHIFT) & PLL_CTRL1_REFDIV_MASK;
	fbdiv = (val >> PLL_CTRL1_FBDIV_SHIFT) & PLL_CTRL1_FBDIV_MASK;

	val = pll_readl(pll, PLL_CTRL2);
	postdiv1 = (val >> PLL_FRAC_CTRL2_POSTDIV1_SHIFT) &
		PLL_FRAC_CTRL2_POSTDIV1_MASK;
	postdiv2 = (val >> PLL_FRAC_CTRL2_POSTDIV2_SHIFT) &
		PLL_FRAC_CTRL2_POSTDIV2_MASK;
	frac = (val >> PLL_FRAC_CTRL2_FRAC_SHIFT) & PLL_FRAC_CTRL2_FRAC_MASK;

	/* get operating mode (int/frac) and calculate rate accordingly */
	rate = parent_rate;
	if (pll_frac_get_mode(hw) == PLL_MODE_FRAC)
		rate *= (fbdiv << 24) + frac;
	else
		rate *= (fbdiv << 24);

	rate = do_div_round_closest(rate, (prediv * postdiv1 * postdiv2) << 24);

	return rate;
}