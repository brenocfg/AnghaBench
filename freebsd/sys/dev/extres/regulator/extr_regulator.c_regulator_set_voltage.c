#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regnode {scalar_t__ ref_cnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* regulator_t ;
struct TYPE_4__ {int min_uvolt; int max_uvolt; struct regnode* regnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  REG_TOPO_SLOCK () ; 
 int /*<<< orphan*/  REG_TOPO_UNLOCK () ; 
 int regnode_set_voltage_checked (struct regnode*,TYPE_1__*,int,int) ; 

int
regulator_set_voltage(regulator_t reg, int min_uvolt, int max_uvolt)
{
	struct regnode *regnode;
	int rv;

	regnode = reg->regnode;
	KASSERT(regnode->ref_cnt > 0,
	   ("Attempt to access unreferenced regulator: %s\n", regnode->name));

	REG_TOPO_SLOCK();

	rv = regnode_set_voltage_checked(regnode, reg, min_uvolt, max_uvolt);
	if (rv == 0) {
		reg->min_uvolt = min_uvolt;
		reg->max_uvolt = max_uvolt;
	}
	REG_TOPO_UNLOCK();
	return (rv);
}