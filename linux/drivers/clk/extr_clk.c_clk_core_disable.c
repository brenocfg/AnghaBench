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
struct clk_core {int enable_count; int flags; struct clk_core* parent; int /*<<< orphan*/  hw; TYPE_1__* ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CLK_IS_CRITICAL ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_clk_disable_complete_rcuidle (struct clk_core*) ; 
 int /*<<< orphan*/  trace_clk_disable_rcuidle (struct clk_core*) ; 

__attribute__((used)) static void clk_core_disable(struct clk_core *core)
{
	lockdep_assert_held(&enable_lock);

	if (!core)
		return;

	if (WARN(core->enable_count == 0, "%s already disabled\n", core->name))
		return;

	if (WARN(core->enable_count == 1 && core->flags & CLK_IS_CRITICAL,
	    "Disabling critical %s\n", core->name))
		return;

	if (--core->enable_count > 0)
		return;

	trace_clk_disable_rcuidle(core);

	if (core->ops->disable)
		core->ops->disable(core->hw);

	trace_clk_disable_complete_rcuidle(core);

	clk_core_disable(core->parent);
}