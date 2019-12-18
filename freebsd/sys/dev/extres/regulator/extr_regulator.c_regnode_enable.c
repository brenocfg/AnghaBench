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
struct regnode {scalar_t__ enable_cnt; struct regnode* parent; } ;

/* Variables and functions */
 int REGNODE_ENABLE (struct regnode*,int,int*) ; 
 int /*<<< orphan*/  REGNODE_UNLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REGNODE_XLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REG_TOPO_ASSERT () ; 
 int /*<<< orphan*/  regnode_delay (int) ; 
 int regnode_resolve_parent (struct regnode*) ; 

int
regnode_enable(struct regnode *regnode)
{
	int udelay;
	int rv;

	REG_TOPO_ASSERT();

	/* Enable regulator for each node in chain, starting from source. */
	rv = regnode_resolve_parent(regnode);
	if (rv != 0)
		return (rv);
	if (regnode->parent != NULL) {
		rv = regnode_enable(regnode->parent);
		if (rv != 0)
			return (rv);
	}

	/* Handle this node. */
	REGNODE_XLOCK(regnode);
	if (regnode->enable_cnt == 0) {
		rv = REGNODE_ENABLE(regnode, true, &udelay);
		if (rv != 0) {
			REGNODE_UNLOCK(regnode);
			return (rv);
		}
		regnode_delay(udelay);
	}
	regnode->enable_cnt++;
	REGNODE_UNLOCK(regnode);
	return (0);
}