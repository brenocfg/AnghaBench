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
typedef  int u32 ;
struct clk_sccg_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PLL_CFG0 ; 
 scalar_t__ PLL_CFG2 ; 
 int /*<<< orphan*/  PLL_DIVF1_MASK ; 
 int /*<<< orphan*/  PLL_DIVF2_MASK ; 
 int /*<<< orphan*/  PLL_DIVQ_MASK ; 
 int /*<<< orphan*/  PLL_DIVR1_MASK ; 
 int /*<<< orphan*/  PLL_DIVR2_MASK ; 
 int SSCG_PLL_BYPASS1_MASK ; 
 int SSCG_PLL_BYPASS2_MASK ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 struct clk_sccg_pll* to_clk_sccg_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_sccg_pll_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct clk_sccg_pll *pll = to_clk_sccg_pll(hw);
	u32 val, divr1, divf1, divr2, divf2, divq;
	u64 temp64;

	val = readl_relaxed(pll->base + PLL_CFG2);
	divr1 = FIELD_GET(PLL_DIVR1_MASK, val);
	divr2 = FIELD_GET(PLL_DIVR2_MASK, val);
	divf1 = FIELD_GET(PLL_DIVF1_MASK, val);
	divf2 = FIELD_GET(PLL_DIVF2_MASK, val);
	divq = FIELD_GET(PLL_DIVQ_MASK, val);

	temp64 = parent_rate;

	val = readl(pll->base + PLL_CFG0);
	if (val & SSCG_PLL_BYPASS2_MASK) {
		temp64 = parent_rate;
	} else if (val & SSCG_PLL_BYPASS1_MASK) {
		temp64 *= divf2;
		do_div(temp64, (divr2 + 1) * (divq + 1));
	} else {
		temp64 *= 2;
		temp64 *= (divf1 + 1) * (divf2 + 1);
		do_div(temp64, (divr1 + 1) * (divr2 + 1) * (divq + 1));
	}

	return temp64;
}