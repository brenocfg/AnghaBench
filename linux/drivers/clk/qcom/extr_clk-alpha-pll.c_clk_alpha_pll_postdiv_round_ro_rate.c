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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll_postdiv {int /*<<< orphan*/  width; TYPE_1__ clkr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CLK_SET_RATE_PARENT ; 
 long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 int PLL_POST_DIV_SHIFT ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll_postdiv*) ; 
 int clk_hw_get_flags (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (int /*<<< orphan*/ ,int) ; 
 int fls (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_alpha_pll_postdiv* to_clk_alpha_pll_postdiv (struct clk_hw*) ; 

__attribute__((used)) static long
clk_alpha_pll_postdiv_round_ro_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long *prate)
{
	struct clk_alpha_pll_postdiv *pll = to_clk_alpha_pll_postdiv(hw);
	u32 ctl, div;

	regmap_read(pll->clkr.regmap, PLL_USER_CTL(pll), &ctl);

	ctl >>= PLL_POST_DIV_SHIFT;
	ctl &= BIT(pll->width) - 1;
	div = 1 << fls(ctl);

	if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
		*prate = clk_hw_round_rate(clk_hw_get_parent(hw), div * rate);

	return DIV_ROUND_UP_ULL((u64)*prate, div);
}