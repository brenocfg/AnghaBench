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
struct TYPE_4__ {struct clknode* clknode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  CLK_TOPO_XLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int clknode_set_parent_by_name (struct clknode*,int /*<<< orphan*/ ) ; 

int
clk_set_parent_by_clk(clk_t clk, clk_t parent)
{
	int rv;
	struct clknode *clknode;
	struct clknode *parentnode;

	clknode = clk->clknode;
	parentnode = parent->clknode;
	KASSERT(clknode->ref_cnt > 0,
	   ("Attempt to access unreferenced clock: %s\n", clknode->name));
	KASSERT(parentnode->ref_cnt > 0,
	   ("Attempt to access unreferenced clock: %s\n", clknode->name));
	CLK_TOPO_XLOCK();
	rv = clknode_set_parent_by_name(clknode, parentnode->name);
	CLK_TOPO_UNLOCK();
	return (rv);
}