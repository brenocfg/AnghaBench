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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dpll_core_ck ; 
 int /*<<< orphan*/  to_clk_hw_omap (struct clk_hw*) ; 

void omap2xxx_clkt_dpllcore_init(struct clk_hw *hw)
{
	WARN(dpll_core_ck, "dpll_core_ck already set - should never happen");
	dpll_core_ck = to_clk_hw_omap(hw);
}