#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {struct regmap* regmap; } ;
struct clk_alpha_pll_postdiv {size_t post_div_shift; size_t num_post_div; TYPE_1__* post_div_table; TYPE_2__ clkr; } ;
struct TYPE_3__ {size_t val; size_t div; } ;

/* Variables and functions */
 size_t PLL_POST_DIV_MASK (struct clk_alpha_pll_postdiv*) ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll_postdiv*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,size_t*) ; 
 struct clk_alpha_pll_postdiv* to_clk_alpha_pll_postdiv (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_trion_pll_postdiv_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_alpha_pll_postdiv *pll = to_clk_alpha_pll_postdiv(hw);
	struct regmap *regmap = pll->clkr.regmap;
	u32 i, div = 1, val;

	regmap_read(regmap, PLL_USER_CTL(pll), &val);

	val >>= pll->post_div_shift;
	val &= PLL_POST_DIV_MASK(pll);

	for (i = 0; i < pll->num_post_div; i++) {
		if (pll->post_div_table[i].val == val) {
			div = pll->post_div_table[i].div;
			break;
		}
	}

	return (parent_rate / div);
}