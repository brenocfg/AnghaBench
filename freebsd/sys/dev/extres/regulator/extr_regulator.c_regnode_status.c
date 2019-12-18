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

/* Variables and functions */
 int REGNODE_STATUS (struct regnode*,int*) ; 
 int /*<<< orphan*/  REGNODE_UNLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REGNODE_XLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REG_TOPO_ASSERT () ; 

int
regnode_status(struct regnode *regnode, int *status)
{
	int rv;

	REG_TOPO_ASSERT();

	REGNODE_XLOCK(regnode);
	rv = REGNODE_STATUS(regnode, status);
	REGNODE_UNLOCK(regnode);
	return (rv);
}