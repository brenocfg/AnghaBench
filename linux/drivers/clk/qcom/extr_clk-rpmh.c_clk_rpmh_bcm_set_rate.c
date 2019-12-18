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
struct clk_rpmh {unsigned long aggr_state; unsigned long unit; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ clk_hw_is_prepared (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_rpmh_bcm_send_cmd (struct clk_rpmh*,int) ; 
 struct clk_rpmh* to_clk_rpmh (struct clk_hw*) ; 

__attribute__((used)) static int clk_rpmh_bcm_set_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long parent_rate)
{
	struct clk_rpmh *c = to_clk_rpmh(hw);

	c->aggr_state = rate / c->unit;
	/*
	 * Since any non-zero value sent to hw would result in enabling the
	 * clock, only send the value if the clock has already been prepared.
	 */
	if (clk_hw_is_prepared(hw))
		clk_rpmh_bcm_send_cmd(c, true);

	return 0;
}