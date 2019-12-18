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
struct phynode {int enable_cnt; } ;

/* Variables and functions */
 int PHYNODE_ENABLE (struct phynode*,int) ; 
 int /*<<< orphan*/  PHYNODE_UNLOCK (struct phynode*) ; 
 int /*<<< orphan*/  PHYNODE_XLOCK (struct phynode*) ; 
 int /*<<< orphan*/  PHY_TOPO_ASSERT () ; 

int
phynode_disable(struct phynode *phynode)
{
	int rv;

	PHY_TOPO_ASSERT();

	PHYNODE_XLOCK(phynode);
	if (phynode->enable_cnt == 1) {
		rv = PHYNODE_ENABLE(phynode, false);
		if (rv != 0) {
			PHYNODE_UNLOCK(phynode);
			return (rv);
		}
	}
	phynode->enable_cnt--;
	PHYNODE_UNLOCK(phynode);
	return (0);
}