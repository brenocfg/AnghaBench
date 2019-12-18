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
struct clknode {scalar_t__ ref_cnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* clk_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; struct clknode* clknode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_TOPO_SLOCK () ; 
 int /*<<< orphan*/  CLK_TOPO_UNLOCK () ; 
 int ENODEV ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_1__* clk_create (struct clknode*,int /*<<< orphan*/ ) ; 
 struct clknode* clknode_get_parent (struct clknode*) ; 

int
clk_get_parent(clk_t clk, clk_t *parent)
{
	struct clknode *clknode;
	struct clknode *parentnode;

	clknode = clk->clknode;
	KASSERT(clknode->ref_cnt > 0,
	   ("Attempt to access unreferenced clock: %s\n", clknode->name));

	CLK_TOPO_SLOCK();
	parentnode = clknode_get_parent(clknode);
	if (parentnode == NULL) {
		CLK_TOPO_UNLOCK();
		return (ENODEV);
	}
	*parent = clk_create(parentnode, clk->dev);
	CLK_TOPO_UNLOCK();
	return (0);
}