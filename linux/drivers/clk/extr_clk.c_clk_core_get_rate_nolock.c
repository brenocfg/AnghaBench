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
struct clk_core {unsigned long rate; scalar_t__ parent; int /*<<< orphan*/  num_parents; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long clk_core_get_rate_nolock(struct clk_core *core)
{
	if (!core)
		return 0;

	if (!core->num_parents || core->parent)
		return core->rate;

	/*
	 * Clk must have a parent because num_parents > 0 but the parent isn't
	 * known yet. Best to return 0 as the rate of this clk until we can
	 * properly recalc the rate based on the parent's rate.
	 */
	return 0;
}