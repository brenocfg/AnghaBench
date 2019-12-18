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
typedef  int u8 ;
typedef  int u32 ;
struct tegra_dfll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_OUTPUT_FORCE ; 
 int DFLL_OUTPUT_FORCE_ENABLE ; 
 int OUT_MASK ; 
 int dfll_readl (struct tegra_dfll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dfll_set_force_output_value(struct tegra_dfll *td, u8 out_val)
{
	u32 val = dfll_readl(td, DFLL_OUTPUT_FORCE);

	val = (val & DFLL_OUTPUT_FORCE_ENABLE) | (out_val & OUT_MASK);
	dfll_writel(td, val, DFLL_OUTPUT_FORCE);
	dfll_wmb(td);

	return dfll_readl(td, DFLL_OUTPUT_FORCE);
}