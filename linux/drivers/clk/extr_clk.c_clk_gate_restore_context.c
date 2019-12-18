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
struct clk_hw {struct clk_core* core; } ;
struct clk_core {TYPE_1__* ops; scalar_t__ enable_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct clk_hw*) ;int /*<<< orphan*/  (* enable ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 
 int /*<<< orphan*/  stub2 (struct clk_hw*) ; 

void clk_gate_restore_context(struct clk_hw *hw)
{
	struct clk_core *core = hw->core;

	if (core->enable_count)
		core->ops->enable(hw);
	else
		core->ops->disable(hw);
}