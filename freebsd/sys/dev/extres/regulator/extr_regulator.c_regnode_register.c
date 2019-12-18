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
struct regnode {scalar_t__ ofw_node; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 int REGNODE_INIT (struct regnode*) ; 
 int /*<<< orphan*/  REG_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  REG_TOPO_XLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct regnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  reglist_link ; 
 int /*<<< orphan*/  regnode_list ; 

struct regnode *
regnode_register(struct regnode *regnode)
{
	int rv;

#ifdef FDT
	if (regnode->ofw_node <= 0)
		regnode->ofw_node = ofw_bus_get_node(regnode->pdev);
	if (regnode->ofw_node <= 0)
		return (NULL);
#endif

	rv = REGNODE_INIT(regnode);
	if (rv != 0) {
		printf("REGNODE_INIT failed: %d\n", rv);
		return (NULL);
	}

	REG_TOPO_XLOCK();
	TAILQ_INSERT_TAIL(&regnode_list, regnode, reglist_link);
	REG_TOPO_UNLOCK();
#ifdef FDT
	OF_device_register_xref(OF_xref_from_node(regnode->ofw_node),
	    regnode->pdev);
#endif
	return (regnode);
}