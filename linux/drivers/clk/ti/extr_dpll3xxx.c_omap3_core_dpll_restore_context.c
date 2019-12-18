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
struct dpll_data {int mult_mask; int div1_mask; int last_rounded_m; int last_rounded_n; int /*<<< orphan*/  mult_div1_reg; } ;
struct clk_hw_omap {int context; struct dpll_data* dpll_data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DPLL_LOCKED ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  _omap3_dpll_write_clken (struct clk_hw_omap*,int) ; 
 int /*<<< orphan*/  _omap3_wait_dpll_status (struct clk_hw_omap*,int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

void omap3_core_dpll_restore_context(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	const struct dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	if (clk->context == DPLL_LOCKED) {
		_omap3_dpll_write_clken(clk, 0x4);
		_omap3_wait_dpll_status(clk, 0);

		v = ti_clk_ll_ops->clk_readl(&dd->mult_div1_reg);
		v &= ~(dd->mult_mask | dd->div1_mask);
		v |= dd->last_rounded_m << __ffs(dd->mult_mask);
		v |= (dd->last_rounded_n - 1) << __ffs(dd->div1_mask);
		ti_clk_ll_ops->clk_writel(v, &dd->mult_div1_reg);

		_omap3_dpll_write_clken(clk, DPLL_LOCKED);
		_omap3_wait_dpll_status(clk, 1);
	} else {
		_omap3_dpll_write_clken(clk, clk->context);
	}
}