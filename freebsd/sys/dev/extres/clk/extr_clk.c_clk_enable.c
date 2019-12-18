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
struct clknode {scalar_t__ ref_cnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* clk_t ;
struct TYPE_3__ {int /*<<< orphan*/  enable_cnt; struct clknode* clknode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_TOPO_SLOCK () ; 
 int /*<<< orphan*/  CLK_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int clknode_enable (struct clknode*) ; 

int
clk_enable(clk_t clk)
{
	int rv;
	struct clknode *clknode;

	clknode = clk->clknode;
	KASSERT(clknode->ref_cnt > 0,
	   ("Attempt to access unreferenced clock: %s\n", clknode->name));
	CLK_TOPO_SLOCK();
	rv = clknode_enable(clknode);
	if (rv == 0)
		clk->enable_cnt++;
	CLK_TOPO_UNLOCK();
	return (rv);
}