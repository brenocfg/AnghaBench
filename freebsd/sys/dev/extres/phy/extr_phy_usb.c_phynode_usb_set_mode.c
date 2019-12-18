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
struct phynode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYNODE_UNLOCK (struct phynode*) ; 
 int PHYNODE_USB_SET_MODE (struct phynode*,int) ; 
 int /*<<< orphan*/  PHYNODE_XLOCK (struct phynode*) ; 
 int /*<<< orphan*/  PHY_TOPO_ASSERT () ; 

int
phynode_usb_set_mode(struct phynode *phynode, int usb_mode)
{
	int rv;

	PHY_TOPO_ASSERT();

	PHYNODE_XLOCK(phynode);
	rv = PHYNODE_USB_SET_MODE(phynode, usb_mode);
	PHYNODE_UNLOCK(phynode);
	return (rv);
}