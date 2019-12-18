#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dpll_data {int enable_mask; int flags; int /*<<< orphan*/  control_reg; } ;
struct clk_hw_omap {struct dpll_data* dpll_data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DPLL_J_TYPE ; 
 int OMAP3XXX_EN_DPLL_LOCKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __ffs (int) ; 
 struct clk_hw_omap* omap3_find_clkoutx2_dpll (struct clk_hw*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

unsigned long omap3_clkoutx2_recalc(struct clk_hw *hw,
				    unsigned long parent_rate)
{
	const struct dpll_data *dd;
	unsigned long rate;
	u32 v;
	struct clk_hw_omap *pclk = NULL;

	if (!parent_rate)
		return 0;

	pclk = omap3_find_clkoutx2_dpll(hw);

	if (!pclk)
		return 0;

	dd = pclk->dpll_data;

	WARN_ON(!dd->enable_mask);

	v = ti_clk_ll_ops->clk_readl(&dd->control_reg) & dd->enable_mask;
	v >>= __ffs(dd->enable_mask);
	if ((v != OMAP3XXX_EN_DPLL_LOCKED) || (dd->flags & DPLL_J_TYPE))
		rate = parent_rate;
	else
		rate = parent_rate * 2;
	return rate;
}