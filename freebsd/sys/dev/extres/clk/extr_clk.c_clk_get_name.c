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
struct TYPE_3__ {struct clknode* clknode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 char* clknode_get_name (struct clknode*) ; 

const char *
clk_get_name(clk_t clk)
{
	const char *name;
	struct clknode *clknode;

	clknode = clk->clknode;
	KASSERT(clknode->ref_cnt > 0,
	   ("Attempt to access unreferenced clock: %s\n", clknode->name));
	name = clknode_get_name(clknode);
	return (name);
}