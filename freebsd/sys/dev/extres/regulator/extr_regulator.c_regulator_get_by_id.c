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
struct regnode {int dummy; } ;
typedef  int /*<<< orphan*/  regulator_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  REG_TOPO_SLOCK () ; 
 int /*<<< orphan*/  REG_TOPO_UNLOCK () ; 
 struct regnode* regnode_find_by_id (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  regulator_create (struct regnode*,int /*<<< orphan*/ ) ; 

int
regulator_get_by_id(device_t cdev, device_t pdev, intptr_t id, regulator_t *reg)
{
	struct regnode *regnode;

	REG_TOPO_SLOCK();

	regnode = regnode_find_by_id(pdev, id);
	if (regnode == NULL) {
		REG_TOPO_UNLOCK();
		return (ENODEV);
	}
	*reg = regulator_create(regnode, cdev);
	REG_TOPO_UNLOCK();

	return (0);
}