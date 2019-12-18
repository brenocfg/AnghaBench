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
struct clk_core {int num_parents; TYPE_1__* parents; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_name; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_core_free_parent_map(struct clk_core *core)
{
	int i = core->num_parents;

	if (!core->num_parents)
		return;

	while (--i >= 0) {
		kfree_const(core->parents[i].name);
		kfree_const(core->parents[i].fw_name);
	}

	kfree(core->parents);
}