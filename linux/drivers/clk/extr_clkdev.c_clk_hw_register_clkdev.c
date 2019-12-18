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
struct clk_lookup {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int do_clk_register_clkdev (struct clk_hw*,struct clk_lookup**,char const*,char const*) ; 

int clk_hw_register_clkdev(struct clk_hw *hw, const char *con_id,
	const char *dev_id)
{
	struct clk_lookup *cl;

	return do_clk_register_clkdev(hw, &cl, con_id, dev_id);
}