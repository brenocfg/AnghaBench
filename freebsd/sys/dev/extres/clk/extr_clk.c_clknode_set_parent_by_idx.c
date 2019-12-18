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
struct clknode {scalar_t__ parent_cnt; int parent_idx; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int CLKNODE_SET_MUX (struct clknode*,int) ; 
 int /*<<< orphan*/  CLK_TOPO_XASSERT () ; 
 int /*<<< orphan*/  clknode_adjust_parent (struct clknode*,int) ; 
 int clknode_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clknode_refresh_cache (struct clknode*,int /*<<< orphan*/ ) ; 

int
clknode_set_parent_by_idx(struct clknode *clknode, int idx)
{
	int rv;
	uint64_t freq;
	int  oldidx;

	/* We have exclusive topology lock, node lock is not needed. */
	CLK_TOPO_XASSERT();

	if (clknode->parent_cnt == 0)
		return (0);

	if (clknode->parent_idx == idx)
		return (0);

	oldidx = clknode->parent_idx;
	clknode_adjust_parent(clknode, idx);
	rv = CLKNODE_SET_MUX(clknode, idx);
	if (rv != 0) {
		clknode_adjust_parent(clknode, oldidx);
		return (rv);
	}
	rv = clknode_get_freq(clknode->parent, &freq);
	if (rv != 0)
		return (rv);
	rv = clknode_refresh_cache(clknode, freq);
	return (rv);
}