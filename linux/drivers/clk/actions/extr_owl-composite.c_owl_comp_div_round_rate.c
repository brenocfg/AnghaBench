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
struct TYPE_2__ {int /*<<< orphan*/  div_hw; } ;
struct owl_composite {TYPE_1__ rate; int /*<<< orphan*/  common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct owl_composite* hw_to_owl_comp (struct clk_hw*) ; 
 long owl_divider_helper_round_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long*) ; 

__attribute__((used)) static long owl_comp_div_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *parent_rate)
{
	struct owl_composite *comp = hw_to_owl_comp(hw);

	return owl_divider_helper_round_rate(&comp->common, &comp->rate.div_hw,
					rate, parent_rate);
}