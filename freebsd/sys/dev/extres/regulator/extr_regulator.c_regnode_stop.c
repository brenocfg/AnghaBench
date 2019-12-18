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
struct regnode {scalar_t__ enable_cnt; int flags; struct regnode* parent; } ;

/* Variables and functions */
 int EBUSY ; 
 int REGNODE_STOP (struct regnode*,int*) ; 
 int /*<<< orphan*/  REGNODE_UNLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REGNODE_XLOCK (struct regnode*) ; 
 int REGULATOR_FLAGS_NOT_DISABLE ; 
 int /*<<< orphan*/  REG_TOPO_ASSERT () ; 
 int /*<<< orphan*/  regnode_delay (int) ; 
 int regnode_resolve_parent (struct regnode*) ; 

int
regnode_stop(struct regnode *regnode, int depth)
{
	int udelay;
	int rv;

	REG_TOPO_ASSERT();
	rv = 0;

	REGNODE_XLOCK(regnode);
	/* The first node must not be enabled. */
	if ((regnode->enable_cnt != 0) && (depth == 0)) {
		REGNODE_UNLOCK(regnode);
		return (EBUSY);
	}
	/* Disable regulator for each node in chain, starting from consumer */
	if ((regnode->enable_cnt == 0) &&
	    ((regnode->flags & REGULATOR_FLAGS_NOT_DISABLE) == 0)) {
		rv = REGNODE_STOP(regnode, &udelay);
		if (rv != 0) {
			REGNODE_UNLOCK(regnode);
			return (rv);
		}
		regnode_delay(udelay);
	}
	REGNODE_UNLOCK(regnode);

	rv = regnode_resolve_parent(regnode);
	if (rv != 0)
		return (rv);
	if (regnode->parent != NULL && regnode->parent->enable_cnt == 0)
		rv = regnode_stop(regnode->parent, depth + 1);
	return (rv);
}