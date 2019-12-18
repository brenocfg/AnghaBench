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
struct clk_core {int num_parents; int /*<<< orphan*/  name; TYPE_1__* parents; struct clk_core* parent; } ;
struct clk {struct clk_core* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool clk_has_parent(struct clk *clk, struct clk *parent)
{
	struct clk_core *core, *parent_core;
	int i;

	/* NULL clocks should be nops, so return success if either is NULL. */
	if (!clk || !parent)
		return true;

	core = clk->core;
	parent_core = parent->core;

	/* Optimize for the case where the parent is already the parent. */
	if (core->parent == parent_core)
		return true;

	for (i = 0; i < core->num_parents; i++)
		if (!strcmp(core->parents[i].name, parent_core->name))
			return true;

	return false;
}