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
typedef  int /*<<< orphan*/  u8 ;
struct clk_core {int num_parents; int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_parent ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct clk_core* clk_core_get_parent_by_index (struct clk_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_core *__clk_init_parent(struct clk_core *core)
{
	u8 index = 0;

	if (core->num_parents > 1 && core->ops->get_parent)
		index = core->ops->get_parent(core->hw);

	return clk_core_get_parent_by_index(core, index);
}