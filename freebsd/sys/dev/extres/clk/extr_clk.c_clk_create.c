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
struct clknode {int /*<<< orphan*/  ref_cnt; } ;
struct clk {scalar_t__ enable_cnt; struct clknode* clknode; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  struct clk* clk_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_TOPO_ASSERT () ; 
 int /*<<< orphan*/  M_CLOCK ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct clk* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static clk_t
clk_create(struct clknode *clknode, device_t dev)
{
	struct clk *clk;

	CLK_TOPO_ASSERT();

	clk =  malloc(sizeof(struct clk), M_CLOCK, M_WAITOK);
	clk->dev = dev;
	clk->clknode = clknode;
	clk->enable_cnt = 0;
	clknode->ref_cnt++;

	return (clk);
}