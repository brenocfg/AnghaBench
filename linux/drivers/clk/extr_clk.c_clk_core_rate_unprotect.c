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
struct clk_core {scalar_t__ protect_count; struct clk_core* parent; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lock ; 

__attribute__((used)) static void clk_core_rate_unprotect(struct clk_core *core)
{
	lockdep_assert_held(&prepare_lock);

	if (!core)
		return;

	if (WARN(core->protect_count == 0,
	    "%s already unprotected\n", core->name))
		return;

	if (--core->protect_count > 0)
		return;

	clk_core_rate_unprotect(core->parent);
}