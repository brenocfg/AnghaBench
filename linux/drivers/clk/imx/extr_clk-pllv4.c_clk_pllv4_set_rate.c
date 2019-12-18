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
struct clk_pllv4 {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long BM_PLL_MULT ; 
 unsigned long BP_PLL_MULT ; 
 unsigned long DEFAULT_MFD ; 
 int EINVAL ; 
 unsigned long MAX_MFD ; 
 scalar_t__ PLL_CFG_OFFSET ; 
 scalar_t__ PLL_DENOM_OFFSET ; 
 scalar_t__ PLL_NUM_OFFSET ; 
 int /*<<< orphan*/  clk_pllv4_is_valid_mult (unsigned long) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 struct clk_pllv4* to_clk_pllv4 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int clk_pllv4_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct clk_pllv4 *pll = to_clk_pllv4(hw);
	u32 val, mult, mfn, mfd = DEFAULT_MFD;
	u64 temp64;

	mult = rate / parent_rate;

	if (!clk_pllv4_is_valid_mult(mult))
		return -EINVAL;

	if (parent_rate <= MAX_MFD)
		mfd = parent_rate;

	temp64 = (u64)(rate - mult * parent_rate);
	temp64 *= mfd;
	do_div(temp64, parent_rate);
	mfn = temp64;

	val = readl_relaxed(pll->base + PLL_CFG_OFFSET);
	val &= ~BM_PLL_MULT;
	val |= mult << BP_PLL_MULT;
	writel_relaxed(val, pll->base + PLL_CFG_OFFSET);

	writel_relaxed(mfn, pll->base + PLL_NUM_OFFSET);
	writel_relaxed(mfd, pll->base + PLL_DENOM_OFFSET);

	return 0;
}