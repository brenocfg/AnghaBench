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
struct clk_core {int flags; scalar_t__ prepare_count; } ;

/* Variables and functions */
 int CLK_OPS_PARENT_ENABLE ; 
 int /*<<< orphan*/  clk_core_disable_lock (struct clk_core*) ; 
 int /*<<< orphan*/  clk_core_disable_unprepare (struct clk_core*) ; 

__attribute__((used)) static void __clk_set_parent_after(struct clk_core *core,
				   struct clk_core *parent,
				   struct clk_core *old_parent)
{
	/*
	 * Finish the migration of prepare state and undo the changes done
	 * for preventing a race with clk_enable().
	 */
	if (core->prepare_count) {
		clk_core_disable_lock(core);
		clk_core_disable_unprepare(old_parent);
	}

	/* re-balance ref counting if CLK_OPS_PARENT_ENABLE is set */
	if (core->flags & CLK_OPS_PARENT_ENABLE) {
		clk_core_disable_unprepare(parent);
		clk_core_disable_unprepare(old_parent);
	}
}