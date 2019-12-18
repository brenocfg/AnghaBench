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
typedef  scalar_t__ u8 ;
struct clk_hw_omap {int /*<<< orphan*/  hw; TYPE_1__* dpll_data; } ;
struct TYPE_2__ {int modes; } ;

/* Variables and functions */
 int DPLL_LOW_POWER_STOP ; 
 int EINVAL ; 
 int /*<<< orphan*/  _omap3_dpll_write_clken (struct clk_hw_omap*,int) ; 
 int /*<<< orphan*/  clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3_dpll_allow_idle (struct clk_hw_omap*) ; 
 scalar_t__ omap3_dpll_autoidle_read (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _omap3_noncore_dpll_stop(struct clk_hw_omap *clk)
{
	u8 ai;

	if (!(clk->dpll_data->modes & (1 << DPLL_LOW_POWER_STOP)))
		return -EINVAL;

	pr_debug("clock: stopping DPLL %s\n", clk_hw_get_name(&clk->hw));

	ai = omap3_dpll_autoidle_read(clk);

	_omap3_dpll_write_clken(clk, DPLL_LOW_POWER_STOP);

	if (ai)
		omap3_dpll_allow_idle(clk);

	return 0;
}