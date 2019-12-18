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
struct clk_core {int num_parents; scalar_t__ hw; TYPE_1__* parents; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ hw; struct clk_core* core; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct clk_core* clk_core_get (struct clk_core*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int clk_fetch_parent_index(struct clk_core *core,
				  struct clk_core *parent)
{
	int i;

	if (!parent)
		return -EINVAL;

	for (i = 0; i < core->num_parents; i++) {
		/* Found it first try! */
		if (core->parents[i].core == parent)
			return i;

		/* Something else is here, so keep looking */
		if (core->parents[i].core)
			continue;

		/* Maybe core hasn't been cached but the hw is all we know? */
		if (core->parents[i].hw) {
			if (core->parents[i].hw == parent->hw)
				break;

			/* Didn't match, but we're expecting a clk_hw */
			continue;
		}

		/* Maybe it hasn't been cached (clk_set_parent() path) */
		if (parent == clk_core_get(core, i))
			break;

		/* Fallback to comparing globally unique names */
		if (core->parents[i].name &&
		    !strcmp(parent->name, core->parents[i].name))
			break;
	}

	if (i == core->num_parents)
		return -EINVAL;

	core->parents[i].core = parent;
	return i;
}