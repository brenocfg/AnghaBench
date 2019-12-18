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
struct stm32_pll_obj {scalar_t__ reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int DIVM_MASK ; 
 int DIVM_SHIFT ; 
 int DIVN_MASK ; 
 int DIVN_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int pll_frac_val (struct clk_hw*) ; 
 int readl_relaxed (scalar_t__) ; 
 struct stm32_pll_obj* to_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long pll_recalc_rate(struct clk_hw *hw,
				     unsigned long parent_rate)
{
	struct stm32_pll_obj *clk_elem = to_pll(hw);
	u32 reg;
	u32 frac, divm, divn;
	u64 rate, rate_frac = 0;

	reg = readl_relaxed(clk_elem->reg + 4);

	divm = ((reg >> DIVM_SHIFT) & DIVM_MASK) + 1;
	divn = ((reg >> DIVN_SHIFT) & DIVN_MASK) + 1;
	rate = (u64)parent_rate * divn;

	do_div(rate, divm);

	frac = pll_frac_val(hw);
	if (frac) {
		rate_frac = (u64)parent_rate * (u64)frac;
		do_div(rate_frac, (divm * 8192));
	}

	return rate + rate_frac;
}