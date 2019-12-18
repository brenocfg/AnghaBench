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
struct pistachio_clk_pll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_STATUS ; 
 int PLL_STATUS_LOCK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int pll_readl (struct pistachio_clk_pll*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pll_lock(struct pistachio_clk_pll *pll)
{
	while (!(pll_readl(pll, PLL_STATUS) & PLL_STATUS_LOCK))
		cpu_relax();
}