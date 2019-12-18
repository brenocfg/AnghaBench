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
struct clk_pllv3 {int div_mask; int div_shift; int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int clk_pllv3_wait_lock (struct clk_pllv3*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pllv3* to_clk_pllv3 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pllv3_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 val, div;

	if (rate == parent_rate * 22)
		div = 1;
	else if (rate == parent_rate * 20)
		div = 0;
	else
		return -EINVAL;

	val = readl_relaxed(pll->base);
	val &= ~(pll->div_mask << pll->div_shift);
	val |= (div << pll->div_shift);
	writel_relaxed(val, pll->base);

	return clk_pllv3_wait_lock(pll);
}