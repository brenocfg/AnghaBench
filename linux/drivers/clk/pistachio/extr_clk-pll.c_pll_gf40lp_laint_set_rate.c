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
struct pistachio_pll_rate_table {int refdiv; int fref; int fbdiv; int postdiv1; int postdiv2; } ;
struct pistachio_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MAX_OUTPUT_LA ; 
 int MAX_VCO_LA ; 
 unsigned long MIN_OUTPUT_LA ; 
 int MIN_PFD ; 
 int MIN_VCO_LA ; 
 int /*<<< orphan*/  PLL_CTRL1 ; 
 int PLL_CTRL1_FBDIV_MASK ; 
 int PLL_CTRL1_FBDIV_SHIFT ; 
 int PLL_CTRL1_REFDIV_MASK ; 
 int PLL_CTRL1_REFDIV_SHIFT ; 
 int PLL_INT_CTRL1_POSTDIV1_MASK ; 
 int PLL_INT_CTRL1_POSTDIV1_SHIFT ; 
 int PLL_INT_CTRL1_POSTDIV2_MASK ; 
 int PLL_INT_CTRL1_POSTDIV2_SHIFT ; 
 char* clk_hw_get_name (struct clk_hw*) ; 
 int div_u64 (int,int) ; 
 struct pistachio_pll_rate_table* pll_get_params (struct pistachio_clk_pll*,unsigned long,unsigned long) ; 
 int pll_gf40lp_laint_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_lock (struct pistachio_clk_pll*) ; 
 int pll_readl (struct pistachio_clk_pll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_writel (struct pistachio_clk_pll*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,...) ; 
 struct pistachio_clk_pll* to_pistachio_pll (struct clk_hw*) ; 

__attribute__((used)) static int pll_gf40lp_laint_set_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long parent_rate)
{
	struct pistachio_clk_pll *pll = to_pistachio_pll(hw);
	struct pistachio_pll_rate_table *params;
	int enabled = pll_gf40lp_laint_is_enabled(hw);
	u32 val, vco, old_postdiv1, old_postdiv2;
	const char *name = clk_hw_get_name(hw);

	if (rate < MIN_OUTPUT_LA || rate > MAX_OUTPUT_LA)
		return -EINVAL;

	params = pll_get_params(pll, parent_rate, rate);
	if (!params || !params->refdiv)
		return -EINVAL;

	vco = div_u64(params->fref * params->fbdiv, params->refdiv);
	if (vco < MIN_VCO_LA || vco > MAX_VCO_LA)
		pr_warn("%s: VCO %u is out of range %lu..%lu\n", name, vco,
			MIN_VCO_LA, MAX_VCO_LA);

	val = div_u64(params->fref, params->refdiv);
	if (val < MIN_PFD)
		pr_warn("%s: PFD %u is too low (min %lu)\n",
			name, val, MIN_PFD);
	if (val > vco / 16)
		pr_warn("%s: PFD %u is too high (max %u)\n",
			name, val, vco / 16);

	val = pll_readl(pll, PLL_CTRL1);

	old_postdiv1 = (val >> PLL_INT_CTRL1_POSTDIV1_SHIFT) &
		       PLL_INT_CTRL1_POSTDIV1_MASK;
	old_postdiv2 = (val >> PLL_INT_CTRL1_POSTDIV2_SHIFT) &
		       PLL_INT_CTRL1_POSTDIV2_MASK;
	if (enabled &&
	    (params->postdiv1 != old_postdiv1 ||
	     params->postdiv2 != old_postdiv2))
		pr_warn("%s: changing postdiv while PLL is enabled\n", name);

	if (params->postdiv2 > params->postdiv1)
		pr_warn("%s: postdiv2 should not exceed postdiv1\n", name);

	val &= ~((PLL_CTRL1_REFDIV_MASK << PLL_CTRL1_REFDIV_SHIFT) |
		 (PLL_CTRL1_FBDIV_MASK << PLL_CTRL1_FBDIV_SHIFT) |
		 (PLL_INT_CTRL1_POSTDIV1_MASK << PLL_INT_CTRL1_POSTDIV1_SHIFT) |
		 (PLL_INT_CTRL1_POSTDIV2_MASK << PLL_INT_CTRL1_POSTDIV2_SHIFT));
	val |= (params->refdiv << PLL_CTRL1_REFDIV_SHIFT) |
		(params->fbdiv << PLL_CTRL1_FBDIV_SHIFT) |
		(params->postdiv1 << PLL_INT_CTRL1_POSTDIV1_SHIFT) |
		(params->postdiv2 << PLL_INT_CTRL1_POSTDIV2_SHIFT);
	pll_writel(pll, val, PLL_CTRL1);

	if (enabled)
		pll_lock(pll);

	return 0;
}