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
struct clk_pllv3 {unsigned long div_mask; scalar_t__ denom_offset; scalar_t__ base; scalar_t__ num_offset; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int clk_pllv3_wait_lock (struct clk_pllv3*) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 struct clk_pllv3* to_clk_pllv3 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int clk_pllv3_av_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_pllv3 *pll = to_clk_pllv3(hw);
	unsigned long min_rate = parent_rate * 27;
	unsigned long max_rate = parent_rate * 54;
	u32 val, div;
	u32 mfn, mfd = 1000000;
	u32 max_mfd = 0x3FFFFFFF;
	u64 temp64;

	if (rate < min_rate || rate > max_rate)
		return -EINVAL;

	if (parent_rate <= max_mfd)
		mfd = parent_rate;

	div = rate / parent_rate;
	temp64 = (u64) (rate - div * parent_rate);
	temp64 *= mfd;
	do_div(temp64, parent_rate);
	mfn = temp64;

	val = readl_relaxed(pll->base);
	val &= ~pll->div_mask;
	val |= div;
	writel_relaxed(val, pll->base);
	writel_relaxed(mfn, pll->base + pll->num_offset);
	writel_relaxed(mfd, pll->base + pll->denom_offset);

	return clk_pllv3_wait_lock(pll);
}