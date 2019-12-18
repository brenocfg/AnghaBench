#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct clk {int exclusive_count; scalar_t__ min_rate; scalar_t__ max_rate; TYPE_1__* core; int /*<<< orphan*/  clks_node; } ;
struct TYPE_3__ {scalar_t__ req_rate; int /*<<< orphan*/  ref; struct module* owner; int /*<<< orphan*/  protect_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_release ; 
 int /*<<< orphan*/  clk_core_rate_unprotect (TYPE_1__*) ; 
 int /*<<< orphan*/  clk_core_set_rate_nolock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int /*<<< orphan*/  free_clk (struct clk*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 

void __clk_put(struct clk *clk)
{
	struct module *owner;

	if (!clk || WARN_ON_ONCE(IS_ERR(clk)))
		return;

	clk_prepare_lock();

	/*
	 * Before calling clk_put, all calls to clk_rate_exclusive_get() from a
	 * given user should be balanced with calls to clk_rate_exclusive_put()
	 * and by that same consumer
	 */
	if (WARN_ON(clk->exclusive_count)) {
		/* We voiced our concern, let's sanitize the situation */
		clk->core->protect_count -= (clk->exclusive_count - 1);
		clk_core_rate_unprotect(clk->core);
		clk->exclusive_count = 0;
	}

	hlist_del(&clk->clks_node);
	if (clk->min_rate > clk->core->req_rate ||
	    clk->max_rate < clk->core->req_rate)
		clk_core_set_rate_nolock(clk->core, clk->core->req_rate);

	owner = clk->core->owner;
	kref_put(&clk->core->ref, __clk_release);

	clk_prepare_unlock();

	module_put(owner);

	free_clk(clk);
}