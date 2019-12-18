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
struct dpll_data {int enable_mask; int last_rounded_m; int mult_mask; int last_rounded_n; int div1_mask; int /*<<< orphan*/  mult_div1_reg; int /*<<< orphan*/  control_reg; } ;
struct clk_hw_omap {int context; struct dpll_data* dpll_data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DPLL_LOCKED ; 
 int __ffs (int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

int omap3_core_dpll_save_context(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	struct dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	v = ti_clk_ll_ops->clk_readl(&dd->control_reg);
	clk->context = (v & dd->enable_mask) >> __ffs(dd->enable_mask);

	if (clk->context == DPLL_LOCKED) {
		v = ti_clk_ll_ops->clk_readl(&dd->mult_div1_reg);
		dd->last_rounded_m = (v & dd->mult_mask) >>
						__ffs(dd->mult_mask);
		dd->last_rounded_n = ((v & dd->div1_mask) >>
						__ffs(dd->div1_mask)) + 1;
	}

	return 0;
}