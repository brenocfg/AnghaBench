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
struct regnode {scalar_t__ ref_cnt; int /*<<< orphan*/  consumers_list; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* regulator_t ;
struct TYPE_5__ {scalar_t__ enable_cnt; struct regnode* regnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_REGULATOR ; 
 int /*<<< orphan*/  REGNODE_UNLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REGNODE_XLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REG_TOPO_SLOCK () ; 
 int /*<<< orphan*/  REG_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  regnode_disable (struct regnode*) ; 

int
regulator_release(regulator_t reg)
{
	struct regnode *regnode;

	regnode = reg->regnode;
	KASSERT(regnode->ref_cnt > 0,
	   ("Attempt to access unreferenced regulator: %s\n", regnode->name));
	REG_TOPO_SLOCK();
	while (reg->enable_cnt > 0) {
		regnode_disable(regnode);
		reg->enable_cnt--;
	}
	REGNODE_XLOCK(regnode);
	TAILQ_REMOVE(&regnode->consumers_list, reg, link);
	regnode->ref_cnt--;
	REGNODE_UNLOCK(regnode);
	REG_TOPO_UNLOCK();

	free(reg, M_REGULATOR);
	return (0);
}