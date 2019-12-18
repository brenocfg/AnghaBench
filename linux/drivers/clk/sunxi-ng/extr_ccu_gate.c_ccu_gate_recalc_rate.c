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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int features; unsigned long prediv; } ;
struct ccu_gate {TYPE_1__ common; } ;

/* Variables and functions */
 int CCU_FEATURE_ALL_PREDIV ; 
 struct ccu_gate* hw_to_ccu_gate (struct clk_hw*) ; 

__attribute__((used)) static unsigned long ccu_gate_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct ccu_gate *cg = hw_to_ccu_gate(hw);
	unsigned long rate = parent_rate;

	if (cg->common.features & CCU_FEATURE_ALL_PREDIV)
		rate /= cg->common.prediv;

	return rate;
}