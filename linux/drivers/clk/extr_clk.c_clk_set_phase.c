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
struct clk {int /*<<< orphan*/  core; scalar_t__ exclusive_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_rate_protect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_core_rate_unprotect (int /*<<< orphan*/ ) ; 
 int clk_core_set_phase_nolock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 

int clk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	if (!clk)
		return 0;

	/* sanity check degrees */
	degrees %= 360;
	if (degrees < 0)
		degrees += 360;

	clk_prepare_lock();

	if (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	ret = clk_core_set_phase_nolock(clk->core, degrees);

	if (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	return ret;
}