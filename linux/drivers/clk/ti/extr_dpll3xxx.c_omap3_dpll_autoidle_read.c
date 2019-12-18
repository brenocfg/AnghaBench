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
struct dpll_data {int autoidle_mask; int /*<<< orphan*/  autoidle_reg; } ;
struct clk_hw_omap {struct dpll_data* dpll_data; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int __ffs (int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static u32 omap3_dpll_autoidle_read(struct clk_hw_omap *clk)
{
	const struct dpll_data *dd;
	u32 v;

	if (!clk || !clk->dpll_data)
		return -EINVAL;

	dd = clk->dpll_data;

	if (!dd->autoidle_mask)
		return -EINVAL;

	v = ti_clk_ll_ops->clk_readl(&dd->autoidle_reg);
	v &= dd->autoidle_mask;
	v >>= __ffs(dd->autoidle_mask);

	return v;
}