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
struct clknode {scalar_t__ parent_cnt; scalar_t__ enable_cnt; struct clknode* parent; } ;

/* Variables and functions */
 int CLKNODE_SET_GATE (struct clknode*,int) ; 
 int /*<<< orphan*/  CLKNODE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLKNODE_XLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLK_TOPO_ASSERT () ; 

int
clknode_enable(struct clknode *clknode)
{
	int rv;

	CLK_TOPO_ASSERT();

	/* Enable clock for each node in chain, starting from source. */
	if (clknode->parent_cnt > 0) {
		rv = clknode_enable(clknode->parent);
		if (rv != 0) {
			return (rv);
		}
	}

	/* Handle this node */
	CLKNODE_XLOCK(clknode);
	if (clknode->enable_cnt == 0) {
		rv = CLKNODE_SET_GATE(clknode, 1);
		if (rv != 0) {
			CLKNODE_UNLOCK(clknode);
			return (rv);
		}
	}
	clknode->enable_cnt++;
	CLKNODE_UNLOCK(clknode);
	return (0);
}