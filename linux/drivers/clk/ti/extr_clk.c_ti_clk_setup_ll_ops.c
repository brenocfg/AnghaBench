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
struct ti_clk_ll_ops {int /*<<< orphan*/  clk_rmw; int /*<<< orphan*/  clk_writel; int /*<<< orphan*/  clk_readl; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  clk_memmap_readl ; 
 int /*<<< orphan*/  clk_memmap_rmw ; 
 int /*<<< orphan*/  clk_memmap_writel ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct ti_clk_ll_ops* ti_clk_ll_ops ; 

int ti_clk_setup_ll_ops(struct ti_clk_ll_ops *ops)
{
	if (ti_clk_ll_ops) {
		pr_err("Attempt to register ll_ops multiple times.\n");
		return -EBUSY;
	}

	ti_clk_ll_ops = ops;
	ops->clk_readl = clk_memmap_readl;
	ops->clk_writel = clk_memmap_writel;
	ops->clk_rmw = clk_memmap_rmw;

	return 0;
}