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
struct clk_hw {int dummy; } ;
struct clk_frac_pll {scalar_t__ base; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PLL_CFG0 ; 
 scalar_t__ PLL_CFG1 ; 
 int PLL_FRAC_DENOM ; 
 int /*<<< orphan*/  PLL_FRAC_DIV_MASK ; 
 int /*<<< orphan*/  PLL_INT_DIV_MASK ; 
 int /*<<< orphan*/  PLL_OUTPUT_DIV_MASK ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct clk_frac_pll* to_clk_frac_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pll_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val, divff, divfi, divq;
	u64 temp64 = parent_rate;
	u64 rate;

	val = readl_relaxed(pll->base + PLL_CFG0);
	divq = (FIELD_GET(PLL_OUTPUT_DIV_MASK, val) + 1) * 2;
	val = readl_relaxed(pll->base + PLL_CFG1);
	divff = FIELD_GET(PLL_FRAC_DIV_MASK, val);
	divfi = FIELD_GET(PLL_INT_DIV_MASK, val);

	temp64 *= 8;
	temp64 *= divff;
	do_div(temp64, PLL_FRAC_DENOM);
	do_div(temp64, divq);

	rate = parent_rate * 8 * (divfi + 1);
	do_div(rate, divq);
	rate += temp64;

	return rate;
}