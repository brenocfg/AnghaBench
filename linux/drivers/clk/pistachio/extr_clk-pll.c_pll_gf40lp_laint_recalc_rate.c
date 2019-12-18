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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct pistachio_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CTRL1 ; 
 unsigned long PLL_CTRL1_FBDIV_MASK ; 
 unsigned long PLL_CTRL1_FBDIV_SHIFT ; 
 unsigned long PLL_CTRL1_REFDIV_MASK ; 
 unsigned long PLL_CTRL1_REFDIV_SHIFT ; 
 unsigned long PLL_INT_CTRL1_POSTDIV1_MASK ; 
 unsigned long PLL_INT_CTRL1_POSTDIV1_SHIFT ; 
 unsigned long PLL_INT_CTRL1_POSTDIV2_MASK ; 
 unsigned long PLL_INT_CTRL1_POSTDIV2_SHIFT ; 
 unsigned long do_div_round_closest (unsigned long,unsigned long) ; 
 unsigned long pll_readl (struct pistachio_clk_pll*,int /*<<< orphan*/ ) ; 
 struct pistachio_clk_pll* to_pistachio_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long pll_gf40lp_laint_recalc_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	struct pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val, prediv, fbdiv, postdiv1, postdiv2;
	u64 rate = parent_rate;

	val = pll_readl(pll, PLL_CTRL1);
	prediv = (val >> PLL_CTRL1_REFDIV_SHIFT) & PLL_CTRL1_REFDIV_MASK;
	fbdiv = (val >> PLL_CTRL1_FBDIV_SHIFT) & PLL_CTRL1_FBDIV_MASK;
	postdiv1 = (val >> PLL_INT_CTRL1_POSTDIV1_SHIFT) &
		PLL_INT_CTRL1_POSTDIV1_MASK;
	postdiv2 = (val >> PLL_INT_CTRL1_POSTDIV2_SHIFT) &
		PLL_INT_CTRL1_POSTDIV2_MASK;

	rate *= fbdiv;
	rate = do_div_round_closest(rate, prediv * postdiv1 * postdiv2);

	return rate;
}