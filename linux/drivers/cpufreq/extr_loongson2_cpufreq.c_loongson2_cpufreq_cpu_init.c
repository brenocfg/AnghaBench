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
struct cpufreq_policy {struct clk* clk; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {unsigned long frequency; } ;

/* Variables and functions */
 unsigned long CPUFREQ_TABLE_END ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_set_rate (struct clk*,unsigned long) ; 
 int cpu_clock_freq ; 
 int /*<<< orphan*/  cpufreq_generic_init (struct cpufreq_policy*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* loongson2_clockmod_table ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int loongson2_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	struct clk *cpuclk;
	int i;
	unsigned long rate;
	int ret;

	cpuclk = clk_get(NULL, "cpu_clk");
	if (IS_ERR(cpuclk)) {
		pr_err("couldn't get CPU clk\n");
		return PTR_ERR(cpuclk);
	}

	rate = cpu_clock_freq / 1000;
	if (!rate) {
		clk_put(cpuclk);
		return -EINVAL;
	}

	/* clock table init */
	for (i = 2;
	     (loongson2_clockmod_table[i].frequency != CPUFREQ_TABLE_END);
	     i++)
		loongson2_clockmod_table[i].frequency = (rate * i) / 8;

	ret = clk_set_rate(cpuclk, rate * 1000);
	if (ret) {
		clk_put(cpuclk);
		return ret;
	}

	policy->clk = cpuclk;
	cpufreq_generic_init(policy, &loongson2_clockmod_table[0], 0);
	return 0;
}