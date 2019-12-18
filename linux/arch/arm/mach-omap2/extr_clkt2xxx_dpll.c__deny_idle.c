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
struct clk_hw_omap {int /*<<< orphan*/  dpll_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap2xxx_cm_set_dpll_disable_autoidle () ; 

__attribute__((used)) static void _deny_idle(struct clk_hw_omap *clk)
{
	if (!clk || !clk->dpll_data)
		return;

	omap2xxx_cm_set_dpll_disable_autoidle();
}