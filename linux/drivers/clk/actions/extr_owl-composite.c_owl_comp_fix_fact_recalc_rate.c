#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk_fixed_factor {int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {struct clk_fixed_factor fix_fact_hw; } ;
struct owl_composite {TYPE_2__* fix_fact_ops; TYPE_1__ rate; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {unsigned long (* recalc_rate ) (int /*<<< orphan*/ *,unsigned long) ;} ;

/* Variables and functions */
 struct owl_composite* hw_to_owl_comp (struct clk_hw*) ; 
 unsigned long stub1 (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long owl_comp_fix_fact_recalc_rate(struct clk_hw *hw,
			unsigned long parent_rate)
{
	struct owl_composite *comp = hw_to_owl_comp(hw);
	struct clk_fixed_factor *fix_fact_hw = &comp->rate.fix_fact_hw;

	return comp->fix_fact_ops->recalc_rate(&fix_fact_hw->hw, parent_rate);

}