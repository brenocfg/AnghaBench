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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_dfll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_OUTPUT_FORCE ; 
 int /*<<< orphan*/  DFLL_OUTPUT_FORCE_ENABLE ; 
 int /*<<< orphan*/  dfll_readl (struct tegra_dfll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfll_set_force_output_enabled(struct tegra_dfll *td, bool enable)
{
	u32 val = dfll_readl(td, DFLL_OUTPUT_FORCE);

	if (enable)
		val |= DFLL_OUTPUT_FORCE_ENABLE;
	else
		val &= ~DFLL_OUTPUT_FORCE_ENABLE;

	dfll_writel(td, val, DFLL_OUTPUT_FORCE);
	dfll_wmb(td);
}