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
struct clk_omap_divider {int shift; int context; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int div_mask (struct clk_omap_divider*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_omap_divider* to_clk_omap_divider (struct clk_hw*) ; 

__attribute__((used)) static void clk_divider_restore_context(struct clk_hw *hw)
{
	struct clk_omap_divider *divider = to_clk_omap_divider(hw);
	u32 val;

	val = ti_clk_ll_ops->clk_readl(&divider->reg);
	val &= ~(div_mask(divider) << divider->shift);
	val |= divider->context << divider->shift;
	ti_clk_ll_ops->clk_writel(val, &divider->reg);
}