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
struct freq_tbl {int dummy; } ;
struct clk_rcg2 {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_rcg2_clear_force_enable (struct clk_hw*) ; 
 int clk_rcg2_configure (struct clk_rcg2*,struct freq_tbl const*) ; 
 int clk_rcg2_set_force_enable (struct clk_hw*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int
clk_rcg2_shared_force_enable_clear(struct clk_hw *hw, const struct freq_tbl *f)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	int ret;

	ret = clk_rcg2_set_force_enable(hw);
	if (ret)
		return ret;

	ret = clk_rcg2_configure(rcg, f);
	if (ret)
		return ret;

	return clk_rcg2_clear_force_enable(hw);
}