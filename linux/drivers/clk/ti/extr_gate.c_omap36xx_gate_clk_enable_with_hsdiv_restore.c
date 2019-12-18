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
struct clk_omap_divider {int shift; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 int omap2_dflt_clk_enable (struct clk_hw*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_omap_divider* to_clk_omap_divider (struct clk_hw*) ; 

__attribute__((used)) static int omap36xx_gate_clk_enable_with_hsdiv_restore(struct clk_hw *hw)
{
	struct clk_omap_divider *parent;
	struct clk_hw *parent_hw;
	u32 dummy_v, orig_v;
	int ret;

	/* Clear PWRDN bit of HSDIVIDER */
	ret = omap2_dflt_clk_enable(hw);

	/* Parent is the x2 node, get parent of parent for the m2 div */
	parent_hw = clk_hw_get_parent(clk_hw_get_parent(hw));
	parent = to_clk_omap_divider(parent_hw);

	/* Restore the dividers */
	if (!ret) {
		orig_v = ti_clk_ll_ops->clk_readl(&parent->reg);
		dummy_v = orig_v;

		/* Write any other value different from the Read value */
		dummy_v ^= (1 << parent->shift);
		ti_clk_ll_ops->clk_writel(dummy_v, &parent->reg);

		/* Write the original divider */
		ti_clk_ll_ops->clk_writel(orig_v, &parent->reg);
	}

	return ret;
}