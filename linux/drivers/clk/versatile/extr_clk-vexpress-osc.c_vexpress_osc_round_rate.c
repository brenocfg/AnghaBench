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
struct vexpress_osc {unsigned long rate_min; unsigned long rate_max; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct vexpress_osc* to_vexpress_osc (struct clk_hw*) ; 

__attribute__((used)) static long vexpress_osc_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	struct vexpress_osc *osc = to_vexpress_osc(hw);

	if (osc->rate_min && rate < osc->rate_min)
		rate = osc->rate_min;

	if (osc->rate_max && rate > osc->rate_max)
		rate = osc->rate_max;

	return rate;
}