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
struct phynode {scalar_t__ ofw_node; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 int PHYNODE_INIT (struct phynode*) ; 
 int /*<<< orphan*/  PHY_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  PHY_TOPO_XLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct phynode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylist_link ; 
 int /*<<< orphan*/  phynode_list ; 
 int /*<<< orphan*/  printf (char*,int) ; 

struct phynode *
phynode_register(struct phynode *phynode)
{
	int rv;

#ifdef FDT
	if (phynode->ofw_node <= 0)
		phynode->ofw_node = ofw_bus_get_node(phynode->pdev);
	if (phynode->ofw_node <= 0)
		return (NULL);
#endif

	rv = PHYNODE_INIT(phynode);
	if (rv != 0) {
		printf("PHYNODE_INIT failed: %d\n", rv);
		return (NULL);
	}

	PHY_TOPO_XLOCK();
	TAILQ_INSERT_TAIL(&phynode_list, phynode, phylist_link);
	PHY_TOPO_UNLOCK();
#ifdef FDT
	OF_device_register_xref(OF_xref_from_node(phynode->ofw_node),
	    phynode->pdev);
#endif
	return (phynode);
}