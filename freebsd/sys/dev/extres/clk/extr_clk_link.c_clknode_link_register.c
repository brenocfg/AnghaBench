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
struct clknode_init_def {int /*<<< orphan*/  flags; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct clk_link_def {struct clknode_init_def clkdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_NODE_LINKED ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,struct clknode_init_def*) ; 
 int /*<<< orphan*/  clknode_link_class ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
clknode_link_register(struct clkdom *clkdom, struct clk_link_def *clkdef)
{
	struct clknode *clk;
	struct clknode_init_def tmp;

	tmp = clkdef->clkdef;
	tmp.flags |= CLK_NODE_LINKED;
	clk = clknode_create(clkdom, &clknode_link_class, &tmp);
	if (clk == NULL)
		return (1);
	clknode_register(clkdom, clk);
	return (0);
}