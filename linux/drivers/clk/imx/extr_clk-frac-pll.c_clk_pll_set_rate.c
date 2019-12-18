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
struct clk_hw {int dummy; } ;
struct clk_frac_pll {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PLL_CFG0 ; 
 scalar_t__ PLL_CFG1 ; 
 unsigned long PLL_FRAC_DENOM ; 
 unsigned long PLL_FRAC_DIV_MASK ; 
 unsigned long PLL_INT_DIV_MASK ; 
 unsigned long PLL_NEWDIV_VAL ; 
 int clk_wait_ack (struct clk_frac_pll*) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 struct clk_frac_pll* to_clk_frac_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int clk_pll_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val, divfi, divff;
	u64 temp64;
	int ret;

	parent_rate *= 8;
	rate *= 2;
	divfi = rate / parent_rate;
	temp64 = parent_rate * divfi;
	temp64 = rate - temp64;
	temp64 *= PLL_FRAC_DENOM;
	do_div(temp64, parent_rate);
	divff = temp64;

	val = readl_relaxed(pll->base + PLL_CFG1);
	val &= ~(PLL_FRAC_DIV_MASK | PLL_INT_DIV_MASK);
	val |= (divff << 7) | (divfi - 1);
	writel_relaxed(val, pll->base + PLL_CFG1);

	val = readl_relaxed(pll->base + PLL_CFG0);
	val &= ~0x1f;
	writel_relaxed(val, pll->base + PLL_CFG0);

	/* Set the NEV_DIV_VAL to reload the DIVFI and DIVFF */
	val = readl_relaxed(pll->base + PLL_CFG0);
	val |= PLL_NEWDIV_VAL;
	writel_relaxed(val, pll->base + PLL_CFG0);

	ret = clk_wait_ack(pll);

	/* clear the NEV_DIV_VAL */
	val = readl_relaxed(pll->base + PLL_CFG0);
	val &= ~PLL_NEWDIV_VAL;
	writel_relaxed(val, pll->base + PLL_CFG0);

	return ret;
}