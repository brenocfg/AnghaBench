#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct phynode {scalar_t__ ref_cnt; int /*<<< orphan*/  consumers_list; } ;
typedef  TYPE_1__* phy_t ;
struct TYPE_5__ {scalar_t__ enable_cnt; struct phynode* phynode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_PHY ; 
 int /*<<< orphan*/  PHYNODE_UNLOCK (struct phynode*) ; 
 int /*<<< orphan*/  PHYNODE_XLOCK (struct phynode*) ; 
 int /*<<< orphan*/  PHY_TOPO_SLOCK () ; 
 int /*<<< orphan*/  PHY_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  phynode_disable (struct phynode*) ; 

void
phy_release(phy_t phy)
{
	struct phynode *phynode;

	phynode = phy->phynode;
	KASSERT(phynode->ref_cnt > 0,
	   ("Attempt to access unreferenced phy.\n"));

	PHY_TOPO_SLOCK();
	while (phy->enable_cnt > 0) {
		phynode_disable(phynode);
		phy->enable_cnt--;
	}
	PHYNODE_XLOCK(phynode);
	TAILQ_REMOVE(&phynode->consumers_list, phy, link);
	phynode->ref_cnt--;
	PHYNODE_UNLOCK(phynode);
	PHY_TOPO_UNLOCK();

	free(phy, M_PHY);
}