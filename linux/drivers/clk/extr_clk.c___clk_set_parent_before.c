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
struct clk_core {int flags; scalar_t__ prepare_count; struct clk_core* parent; } ;

/* Variables and functions */
 int CLK_OPS_PARENT_ENABLE ; 
 int /*<<< orphan*/  clk_core_enable_lock (struct clk_core*) ; 
 int /*<<< orphan*/  clk_core_prepare_enable (struct clk_core*) ; 
 unsigned long clk_enable_lock () ; 
 int /*<<< orphan*/  clk_enable_unlock (unsigned long) ; 
 int /*<<< orphan*/  clk_reparent (struct clk_core*,struct clk_core*) ; 

__attribute__((used)) static struct clk_core *__clk_set_parent_before(struct clk_core *core,
					   struct clk_core *parent)
{
	unsigned long flags;
	struct clk_core *old_parent = core->parent;

	/*
	 * 1. enable parents for CLK_OPS_PARENT_ENABLE clock
	 *
	 * 2. Migrate prepare state between parents and prevent race with
	 * clk_enable().
	 *
	 * If the clock is not prepared, then a race with
	 * clk_enable/disable() is impossible since we already have the
	 * prepare lock (future calls to clk_enable() need to be preceded by
	 * a clk_prepare()).
	 *
	 * If the clock is prepared, migrate the prepared state to the new
	 * parent and also protect against a race with clk_enable() by
	 * forcing the clock and the new parent on.  This ensures that all
	 * future calls to clk_enable() are practically NOPs with respect to
	 * hardware and software states.
	 *
	 * See also: Comment for clk_set_parent() below.
	 */

	/* enable old_parent & parent if CLK_OPS_PARENT_ENABLE is set */
	if (core->flags & CLK_OPS_PARENT_ENABLE) {
		clk_core_prepare_enable(old_parent);
		clk_core_prepare_enable(parent);
	}

	/* migrate prepare count if > 0 */
	if (core->prepare_count) {
		clk_core_prepare_enable(parent);
		clk_core_enable_lock(core);
	}

	/* update the clk tree topology */
	flags = clk_enable_lock();
	clk_reparent(core, parent);
	clk_enable_unlock(flags);

	return old_parent;
}