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
struct TYPE_2__ {int /*<<< orphan*/  always_on; } ;
struct regnode {int enable_cnt; int flags; struct regnode* parent; TYPE_1__ std_param; } ;

/* Variables and functions */
 int REGNODE_ENABLE (struct regnode*,int,int*) ; 
 int /*<<< orphan*/  REGNODE_UNLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REGNODE_XLOCK (struct regnode*) ; 
 int REGULATOR_FLAGS_NOT_DISABLE ; 
 int /*<<< orphan*/  REG_TOPO_ASSERT () ; 
 int /*<<< orphan*/  regnode_delay (int) ; 
 int regnode_resolve_parent (struct regnode*) ; 

int
regnode_disable(struct regnode *regnode)
{
	int udelay;
	int rv;

	REG_TOPO_ASSERT();
	rv = 0;

	REGNODE_XLOCK(regnode);
	/* Disable regulator for each node in chain, starting from consumer. */
	if (regnode->enable_cnt == 1 &&
	    (regnode->flags & REGULATOR_FLAGS_NOT_DISABLE) == 0 &&
	    !regnode->std_param.always_on) {
		rv = REGNODE_ENABLE(regnode, false, &udelay);
		if (rv != 0) {
			REGNODE_UNLOCK(regnode);
			return (rv);
		}
		regnode_delay(udelay);
	}
	regnode->enable_cnt--;
	REGNODE_UNLOCK(regnode);

	rv = regnode_resolve_parent(regnode);
	if (rv != 0)
		return (rv);
	if (regnode->parent != NULL)
		rv = regnode_disable(regnode->parent);
	return (rv);
}