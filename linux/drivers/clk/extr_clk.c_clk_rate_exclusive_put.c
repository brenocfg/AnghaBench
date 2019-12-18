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
struct clk {scalar_t__ exclusive_count; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_core_rate_unprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 

void clk_rate_exclusive_put(struct clk *clk)
{
	if (!clk)
		return;

	clk_prepare_lock();

	/*
	 * if there is something wrong with this consumer protect count, stop
	 * here before messing with the provider
	 */
	if (WARN_ON(clk->exclusive_count <= 0))
		goto out;

	clk_core_rate_unprotect(clk->core);
	clk->exclusive_count--;
out:
	clk_prepare_unlock();
}