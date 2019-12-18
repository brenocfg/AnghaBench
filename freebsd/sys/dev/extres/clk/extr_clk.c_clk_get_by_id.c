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
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_TOPO_SLOCK () ; 
 int /*<<< orphan*/  CLK_TOPO_UNLOCK () ; 
 int ENODEV ; 
 int /*<<< orphan*/  clk_create (struct clknode*,int /*<<< orphan*/ ) ; 
 struct clknode* clknode_find_by_id (struct clkdom*,intptr_t) ; 

int
clk_get_by_id(device_t dev, struct clkdom *clkdom, intptr_t id, clk_t *clk)
{
	struct clknode *clknode;

	CLK_TOPO_SLOCK();

	clknode = clknode_find_by_id(clkdom, id);
	if (clknode == NULL) {
		CLK_TOPO_UNLOCK();
		return (ENODEV);
	}
	*clk = clk_create(clknode, dev);
	CLK_TOPO_UNLOCK();

	return (0);
}