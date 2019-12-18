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
struct clk_prcc {int cg_sel; int is_enabled; scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PRCC_KCKEN ; 
 scalar_t__ PRCC_KCKSR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (scalar_t__) ; 
 struct clk_prcc* to_clk_prcc (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int clk_prcc_kclk_enable(struct clk_hw *hw)
{
	struct clk_prcc *clk = to_clk_prcc(hw);

	writel(clk->cg_sel, (clk->base + PRCC_KCKEN));
	while (!(readl(clk->base + PRCC_KCKSR) & clk->cg_sel))
		cpu_relax();

	clk->is_enabled = 1;
	return 0;
}