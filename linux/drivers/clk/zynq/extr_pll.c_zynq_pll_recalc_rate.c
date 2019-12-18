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
typedef  unsigned long u32 ;
struct zynq_pll {int /*<<< orphan*/  pll_ctrl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long PLLCTRL_FBDIV_MASK ; 
 unsigned long PLLCTRL_FBDIV_SHIFT ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 struct zynq_pll* to_zynq_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long zynq_pll_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct zynq_pll *clk = to_zynq_pll(hw);
	u32 fbdiv;

	/*
	 * makes probably sense to redundantly save fbdiv in the struct
	 * zynq_pll to save the IO access.
	 */
	fbdiv = (readl(clk->pll_ctrl) & PLLCTRL_FBDIV_MASK) >>
			PLLCTRL_FBDIV_SHIFT;

	return parent_rate * fbdiv;
}