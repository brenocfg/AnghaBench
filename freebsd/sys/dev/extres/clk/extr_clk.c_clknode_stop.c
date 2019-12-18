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
struct clknode {scalar_t__ enable_cnt; int flags; scalar_t__ parent_cnt; struct clknode* parent; } ;

/* Variables and functions */
 int CLKNODE_SET_GATE (struct clknode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLKNODE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLKNODE_XLOCK (struct clknode*) ; 
 int CLK_NODE_CANNOT_STOP ; 
 int /*<<< orphan*/  CLK_TOPO_ASSERT () ; 
 int EBUSY ; 

int
clknode_stop(struct clknode *clknode, int depth)
{
	int rv;

	CLK_TOPO_ASSERT();
	rv = 0;

	CLKNODE_XLOCK(clknode);
	/* The first node cannot be enabled. */
	if ((clknode->enable_cnt != 0) && (depth == 0)) {
		CLKNODE_UNLOCK(clknode);
		return (EBUSY);
	}
	/* Stop clock for each node in chain, starting from consumer. */
	if ((clknode->enable_cnt == 0) &&
	    ((clknode->flags & CLK_NODE_CANNOT_STOP) == 0)) {
		rv = CLKNODE_SET_GATE(clknode, 0);
		if (rv != 0) {
			CLKNODE_UNLOCK(clknode);
			return (rv);
		}
	}
	CLKNODE_UNLOCK(clknode);

	if (clknode->parent_cnt > 0)
		rv = clknode_stop(clknode->parent, depth + 1);
	return (rv);
}