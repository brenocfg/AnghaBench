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
struct clk_rcg2 {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_rcg2_clear_force_enable (struct clk_hw*) ; 
 int clk_rcg2_set_force_enable (struct clk_hw*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 
 int update_config (struct clk_rcg2*) ; 

__attribute__((used)) static int clk_rcg2_shared_enable(struct clk_hw *hw)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	int ret;

	/*
	 * Set the update bit because required configuration has already
	 * been written in clk_rcg2_shared_set_rate()
	 */
	ret = clk_rcg2_set_force_enable(hw);
	if (ret)
		return ret;

	ret = update_config(rcg);
	if (ret)
		return ret;

	return clk_rcg2_clear_force_enable(hw);
}