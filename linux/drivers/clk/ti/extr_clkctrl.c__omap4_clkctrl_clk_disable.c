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
union omap4_timeout {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw_omap {int flags; scalar_t__ clkdm; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  enable_bit; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clkdm_clk_disable ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int NO_IDLEST ; 
 int /*<<< orphan*/  OMAP4_MAX_MODULE_DISABLE_TIME ; 
 int /*<<< orphan*/  OMAP4_MODULEMODE_MASK ; 
 int /*<<< orphan*/  _omap4_is_idle (int /*<<< orphan*/ ) ; 
 scalar_t__ _omap4_is_timeout (union omap4_timeout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

__attribute__((used)) static void _omap4_clkctrl_clk_disable(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 val;
	union omap4_timeout timeout = { 0 };

	if (!clk->enable_bit)
		goto exit;

	val = ti_clk_ll_ops->clk_readl(&clk->enable_reg);

	val &= ~OMAP4_MODULEMODE_MASK;

	ti_clk_ll_ops->clk_writel(val, &clk->enable_reg);

	if (clk->flags & NO_IDLEST)
		goto exit;

	/* Wait until module is disabled */
	while (!_omap4_is_idle(ti_clk_ll_ops->clk_readl(&clk->enable_reg))) {
		if (_omap4_is_timeout(&timeout,
				      OMAP4_MAX_MODULE_DISABLE_TIME)) {
			pr_err("%s: failed to disable\n", clk_hw_get_name(hw));
			break;
		}
	}

exit:
	if (clk->clkdm)
		ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
}