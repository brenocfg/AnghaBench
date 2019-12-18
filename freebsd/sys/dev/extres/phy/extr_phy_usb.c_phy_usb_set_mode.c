#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phynode {scalar_t__ ref_cnt; } ;
typedef  TYPE_1__* phy_t ;
struct TYPE_3__ {struct phynode* phynode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PHY_TOPO_SLOCK () ; 
 int /*<<< orphan*/  PHY_TOPO_UNLOCK () ; 
 int phynode_usb_set_mode (struct phynode*,int) ; 

int phy_usb_set_mode(phy_t phy, int usb_mode)
{
	int rv;
	struct phynode *phynode;

	phynode = phy->phynode;
	KASSERT(phynode->ref_cnt > 0,
	   ("Attempt to access unreferenced phy.\n"));

	PHY_TOPO_SLOCK();
	rv = phynode_usb_set_mode(phynode, usb_mode);
	PHY_TOPO_UNLOCK();
	return (rv);
}