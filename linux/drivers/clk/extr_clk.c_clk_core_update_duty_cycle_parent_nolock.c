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
struct clk_core {int flags; TYPE_1__* parent; int /*<<< orphan*/  duty; } ;
struct TYPE_2__ {int /*<<< orphan*/  duty; } ;

/* Variables and functions */
 int CLK_DUTY_CYCLE_PARENT ; 
 int /*<<< orphan*/  clk_core_reset_duty_cycle_nolock (struct clk_core*) ; 
 int clk_core_update_duty_cycle_nolock (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int clk_core_update_duty_cycle_parent_nolock(struct clk_core *core)
{
	int ret = 0;

	if (core->parent &&
	    core->flags & CLK_DUTY_CYCLE_PARENT) {
		ret = clk_core_update_duty_cycle_nolock(core->parent);
		memcpy(&core->duty, &core->parent->duty, sizeof(core->duty));
	} else {
		clk_core_reset_duty_cycle_nolock(core);
	}

	return ret;
}