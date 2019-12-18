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
struct clk_parent_map {struct clk_core* core; scalar_t__ name; TYPE_1__* hw; } ;
struct clk_core {struct clk_parent_map* parents; } ;
struct TYPE_2__ {struct clk_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct clk_core* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk_core*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk_core*) ; 
 struct clk_core* clk_core_get (struct clk_core*,size_t) ; 
 struct clk_core* clk_core_lookup (scalar_t__) ; 

__attribute__((used)) static void clk_core_fill_parent_index(struct clk_core *core, u8 index)
{
	struct clk_parent_map *entry = &core->parents[index];
	struct clk_core *parent = ERR_PTR(-ENOENT);

	if (entry->hw) {
		parent = entry->hw->core;
		/*
		 * We have a direct reference but it isn't registered yet?
		 * Orphan it and let clk_reparent() update the orphan status
		 * when the parent is registered.
		 */
		if (!parent)
			parent = ERR_PTR(-EPROBE_DEFER);
	} else {
		parent = clk_core_get(core, index);
		if (IS_ERR(parent) && PTR_ERR(parent) == -ENOENT && entry->name)
			parent = clk_core_lookup(entry->name);
	}

	/* Only cache it if it's not an error */
	if (!IS_ERR(parent))
		entry->core = parent;
}