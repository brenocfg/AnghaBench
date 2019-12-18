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
 int REGNODE_SET_VOLTAGE (struct regnode*,int,int,int*) ; 
 int /*<<< orphan*/  REGNODE_UNLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REGNODE_XLOCK (struct regnode*) ; 
 int /*<<< orphan*/  REG_TOPO_ASSERT () ; 
 int /*<<< orphan*/  regnode_delay (int) ; 

int
regnode_set_voltage(struct regnode *regnode, int min_uvolt, int max_uvolt)
{
	int udelay;
	int rv;

	REG_TOPO_ASSERT();

	REGNODE_XLOCK(regnode);

	rv = REGNODE_SET_VOLTAGE(regnode, min_uvolt, max_uvolt, &udelay);
	if (rv == 0)
		regnode_delay(udelay);
	REGNODE_UNLOCK(regnode);
	return (rv);
}