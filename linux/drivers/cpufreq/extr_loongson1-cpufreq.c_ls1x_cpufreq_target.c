#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  clk; TYPE_1__* freq_table; int /*<<< orphan*/  cpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  mux_clk; int /*<<< orphan*/  osc_clk; } ;
struct TYPE_3__ {unsigned int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  LS1X_CLK_PLL_DIV ; 
 int RST_CPU ; 
 int RST_CPU_EN ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* cpufreq ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int) ; 
 struct device* get_cpu_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ls1x_cpufreq_target(struct cpufreq_policy *policy,
			       unsigned int index)
{
	struct device *cpu_dev = get_cpu_device(policy->cpu);
	unsigned int old_freq, new_freq;

	old_freq = policy->cur;
	new_freq = policy->freq_table[index].frequency;

	/*
	 * The procedure of reconfiguring CPU clk is as below.
	 *
	 *  - Reparent CPU clk to OSC clk
	 *  - Reset CPU clock (very important)
	 *  - Reconfigure CPU DIV
	 *  - Reparent CPU clk back to CPU DIV clk
	 */

	clk_set_parent(policy->clk, cpufreq->osc_clk);
	__raw_writel(__raw_readl(LS1X_CLK_PLL_DIV) | RST_CPU_EN | RST_CPU,
		     LS1X_CLK_PLL_DIV);
	__raw_writel(__raw_readl(LS1X_CLK_PLL_DIV) & ~(RST_CPU_EN | RST_CPU),
		     LS1X_CLK_PLL_DIV);
	clk_set_rate(cpufreq->mux_clk, new_freq * 1000);
	clk_set_parent(policy->clk, cpufreq->mux_clk);
	dev_dbg(cpu_dev, "%u KHz --> %u KHz\n", old_freq, new_freq);

	return 0;
}