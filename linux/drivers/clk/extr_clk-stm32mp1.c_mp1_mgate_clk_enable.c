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
struct stm32_clk_mgate {int /*<<< orphan*/  mask; TYPE_1__* mgate; } ;
struct clk_hw {int dummy; } ;
struct clk_gate {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp1_gate_clk_enable (struct clk_hw*) ; 
 struct clk_gate* to_clk_gate (struct clk_hw*) ; 
 struct stm32_clk_mgate* to_clk_mgate (struct clk_gate*) ; 

__attribute__((used)) static int mp1_mgate_clk_enable(struct clk_hw *hw)
{
	struct clk_gate *gate = to_clk_gate(hw);
	struct stm32_clk_mgate *clk_mgate = to_clk_mgate(gate);

	clk_mgate->mgate->flag |= clk_mgate->mask;

	mp1_gate_clk_enable(hw);

	return  0;
}