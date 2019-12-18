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
struct clknode {scalar_t__ ref_cnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* clk_t ;
struct TYPE_4__ {scalar_t__ enable_cnt; struct clknode* clknode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKNODE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLKNODE_XLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLK_TOPO_SLOCK () ; 
 int /*<<< orphan*/  CLK_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CLOCK ; 
 int /*<<< orphan*/  clknode_disable (struct clknode*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
clk_release(clk_t clk)
{
	struct clknode *clknode;

	clknode = clk->clknode;
	KASSERT(clknode->ref_cnt > 0,
	   ("Attempt to access unreferenced clock: %s\n", clknode->name));
	CLK_TOPO_SLOCK();
	while (clk->enable_cnt > 0) {
		clknode_disable(clknode);
		clk->enable_cnt--;
	}
	CLKNODE_XLOCK(clknode);
	clknode->ref_cnt--;
	CLKNODE_UNLOCK(clknode);
	CLK_TOPO_UNLOCK();

	free(clk, M_CLOCK);
	return (0);
}