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
struct clk_prcmu {int /*<<< orphan*/  cg_sel; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long prcmu_clock_rate (int /*<<< orphan*/ ) ; 
 struct clk_prcmu* to_clk_prcmu (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_prcmu_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct clk_prcmu *clk = to_clk_prcmu(hw);
	return prcmu_clock_rate(clk->cg_sel);
}