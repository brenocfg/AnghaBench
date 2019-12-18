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
struct regnode {scalar_t__ ref_cnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* regulator_t ;
struct TYPE_3__ {struct regnode* regnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  REG_TOPO_SLOCK () ; 
 int /*<<< orphan*/  REG_TOPO_UNLOCK () ; 
 int regnode_get_voltage (struct regnode*,int*) ; 

int
regulator_get_voltage(regulator_t reg, int *uvolt)
{
	int rv;
	struct regnode *regnode;

	regnode = reg->regnode;
	KASSERT(regnode->ref_cnt > 0,
	   ("Attempt to access unreferenced regulator: %s\n", regnode->name));

	REG_TOPO_SLOCK();
	rv = regnode_get_voltage(regnode, uvolt);
	REG_TOPO_UNLOCK();
	return (rv);
}