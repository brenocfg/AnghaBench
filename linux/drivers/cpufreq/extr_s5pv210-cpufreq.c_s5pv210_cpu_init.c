#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {scalar_t__ cpu; void* clk; int /*<<< orphan*/  suspend_freq; } ;
struct TYPE_2__ {int refresh; void* freq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 unsigned long LPDDR ; 
 unsigned long LPDDR2 ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SLEEP_FREQ ; 
 unsigned long check_mem_type (scalar_t__) ; 
 void* clk_get (int /*<<< orphan*/ *,char*) ; 
 void* clk_get_rate (void*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  cpufreq_generic_init (struct cpufreq_policy*,int /*<<< orphan*/ ,int) ; 
 void* dmc0_clk ; 
 void* dmc1_clk ; 
 scalar_t__* dmc_base ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int readl_relaxed (scalar_t__) ; 
 TYPE_1__* s5pv210_dram_conf ; 
 int /*<<< orphan*/  s5pv210_freq_table ; 

__attribute__((used)) static int s5pv210_cpu_init(struct cpufreq_policy *policy)
{
	unsigned long mem_type;
	int ret;

	policy->clk = clk_get(NULL, "armclk");
	if (IS_ERR(policy->clk))
		return PTR_ERR(policy->clk);

	dmc0_clk = clk_get(NULL, "sclk_dmc0");
	if (IS_ERR(dmc0_clk)) {
		ret = PTR_ERR(dmc0_clk);
		goto out_dmc0;
	}

	dmc1_clk = clk_get(NULL, "hclk_msys");
	if (IS_ERR(dmc1_clk)) {
		ret = PTR_ERR(dmc1_clk);
		goto out_dmc1;
	}

	if (policy->cpu != 0) {
		ret = -EINVAL;
		goto out_dmc1;
	}

	/*
	 * check_mem_type : This driver only support LPDDR & LPDDR2.
	 * other memory type is not supported.
	 */
	mem_type = check_mem_type(dmc_base[0]);

	if ((mem_type != LPDDR) && (mem_type != LPDDR2)) {
		pr_err("CPUFreq doesn't support this memory type\n");
		ret = -EINVAL;
		goto out_dmc1;
	}

	/* Find current refresh counter and frequency each DMC */
	s5pv210_dram_conf[0].refresh = (readl_relaxed(dmc_base[0] + 0x30) * 1000);
	s5pv210_dram_conf[0].freq = clk_get_rate(dmc0_clk);

	s5pv210_dram_conf[1].refresh = (readl_relaxed(dmc_base[1] + 0x30) * 1000);
	s5pv210_dram_conf[1].freq = clk_get_rate(dmc1_clk);

	policy->suspend_freq = SLEEP_FREQ;
	cpufreq_generic_init(policy, s5pv210_freq_table, 40000);
	return 0;

out_dmc1:
	clk_put(dmc0_clk);
out_dmc0:
	clk_put(policy->clk);
	return ret;
}