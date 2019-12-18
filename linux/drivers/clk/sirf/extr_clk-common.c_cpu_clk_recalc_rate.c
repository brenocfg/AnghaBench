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
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 

__attribute__((used)) static unsigned long cpu_clk_recalc_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	/*
	 * SiRF SoC has not cpu clock control,
	 * So return the parent pll rate.
	 */
	struct clk_hw *parent_clk = clk_hw_get_parent(hw);
	return clk_hw_get_rate(parent_clk);
}