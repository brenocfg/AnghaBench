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
struct clk_omap_divider {unsigned int shift; int flags; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int CLK_DIVIDER_ALLOW_ZERO ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 unsigned int _get_div (struct clk_omap_divider*,unsigned int) ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 unsigned int div_mask (struct clk_omap_divider*) ; 
 unsigned int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_omap_divider* to_clk_omap_divider (struct clk_hw*) ; 

__attribute__((used)) static unsigned long ti_clk_divider_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_omap_divider *divider = to_clk_omap_divider(hw);
	unsigned int div, val;

	val = ti_clk_ll_ops->clk_readl(&divider->reg) >> divider->shift;
	val &= div_mask(divider);

	div = _get_div(divider, val);
	if (!div) {
		WARN(!(divider->flags & CLK_DIVIDER_ALLOW_ZERO),
		     "%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
		     clk_hw_get_name(hw));
		return parent_rate;
	}

	return DIV_ROUND_UP(parent_rate, div);
}