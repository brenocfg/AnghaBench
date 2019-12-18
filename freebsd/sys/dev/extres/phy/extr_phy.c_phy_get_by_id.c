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
typedef  int /*<<< orphan*/  phy_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PHY_TOPO_SLOCK () ; 
 int /*<<< orphan*/  PHY_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  phy_create (struct phynode*,int /*<<< orphan*/ ) ; 
 struct phynode* phynode_find_by_id (int /*<<< orphan*/ ,intptr_t) ; 

int
phy_get_by_id(device_t consumer_dev, device_t provider_dev, intptr_t id,
    phy_t *phy)
{
	struct phynode *phynode;

	PHY_TOPO_SLOCK();

	phynode = phynode_find_by_id(provider_dev, id);
	if (phynode == NULL) {
		PHY_TOPO_UNLOCK();
		return (ENODEV);
	}
	*phy = phy_create(phynode, consumer_dev);
	PHY_TOPO_UNLOCK();

	return (0);
}