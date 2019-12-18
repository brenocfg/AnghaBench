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
struct sun9i_a80_cpus_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SUN9I_CPUS_DIV_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN9I_CPUS_MUX_GET_PARENT (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN9I_CPUS_MUX_PARENT_PLL4 ; 
 int SUN9I_CPUS_PLL4_DIV_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct sun9i_a80_cpus_clk* to_sun9i_a80_cpus_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long sun9i_a80_cpus_clk_recalc_rate(struct clk_hw *hw,
						    unsigned long parent_rate)
{
	struct sun9i_a80_cpus_clk *cpus = to_sun9i_a80_cpus_clk(hw);
	unsigned long rate;
	u32 reg;

	/* Fetch the register value */
	reg = readl(cpus->reg);

	/* apply pre-divider first if parent is pll4 */
	if (SUN9I_CPUS_MUX_GET_PARENT(reg) == SUN9I_CPUS_MUX_PARENT_PLL4)
		parent_rate /= SUN9I_CPUS_PLL4_DIV_GET(reg) + 1;

	/* clk divider */
	rate = parent_rate / (SUN9I_CPUS_DIV_GET(reg) + 1);

	return rate;
}