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
typedef  int /*<<< orphan*/  uint64_t ;
struct clknode {int parent_cnt; int parent_idx; struct clknode* parent; int /*<<< orphan*/ ** parent_names; } ;

/* Variables and functions */
 int CLKNODE_SET_MUX (struct clknode*,int) ; 
 int /*<<< orphan*/  CLKNODE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLK_TOPO_XASSERT () ; 
 int ENXIO ; 
 int /*<<< orphan*/  clknode_adjust_parent (struct clknode*,int) ; 
 int clknode_get_freq (struct clknode*,int /*<<< orphan*/ *) ; 
 int clknode_refresh_cache (struct clknode*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

int
clknode_set_parent_by_name(struct clknode *clknode, const char *name)
{
	int rv;
	uint64_t freq;
	int  oldidx, idx;

	/* We have exclusive topology lock, node lock is not needed. */
	CLK_TOPO_XASSERT();

	if (clknode->parent_cnt == 0)
		return (0);

	/*
	 * If this node doesnt have mux, then passthrough request to parent.
	 * This feature is used in clock domain initialization and allows us to
	 * set clock source and target frequency on the tail node of the clock
	 * chain.
	 */
	if (clknode->parent_cnt == 1) {
		rv = clknode_set_parent_by_name(clknode->parent, name);
		return (rv);
	}

	for (idx = 0; idx < clknode->parent_cnt; idx++) {
		if (clknode->parent_names[idx] == NULL)
			continue;
		if (strcmp(clknode->parent_names[idx], name) == 0)
			break;
	}
	if (idx >= clknode->parent_cnt) {
		return (ENXIO);
	}
	if (clknode->parent_idx == idx)
		return (0);

	oldidx = clknode->parent_idx;
	clknode_adjust_parent(clknode, idx);
	rv = CLKNODE_SET_MUX(clknode, idx);
	if (rv != 0) {
		clknode_adjust_parent(clknode, oldidx);
		CLKNODE_UNLOCK(clknode);
		return (rv);
	}
	rv = clknode_get_freq(clknode->parent, &freq);
	if (rv != 0)
		return (rv);
	rv = clknode_refresh_cache(clknode, freq);
	return (rv);
}