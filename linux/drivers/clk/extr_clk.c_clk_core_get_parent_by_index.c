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
typedef  size_t u8 ;
struct clk_core {size_t num_parents; TYPE_1__* parents; } ;
struct TYPE_2__ {struct clk_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_fill_parent_index (struct clk_core*,size_t) ; 

__attribute__((used)) static struct clk_core *clk_core_get_parent_by_index(struct clk_core *core,
							 u8 index)
{
	if (!core || index >= core->num_parents || !core->parents)
		return NULL;

	if (!core->parents[index].core)
		clk_core_fill_parent_index(core, index);

	return core->parents[index].core;
}