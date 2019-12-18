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
struct cpufreq_policy {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {struct clk* clk; TYPE_1__* freq_tbl; } ;
struct TYPE_3__ {int frequency; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 long clk_round_rate (struct clk*,long) ; 
 int clk_set_rate (struct clk*,long) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct clk* spear1340_cpu_get_possible_parent (long) ; 
 int spear1340_set_cpu_rate (struct clk*,long) ; 
 TYPE_2__ spear_cpufreq ; 

__attribute__((used)) static int spear_cpufreq_target(struct cpufreq_policy *policy,
		unsigned int index)
{
	long newfreq;
	struct clk *srcclk;
	int ret, mult = 1;

	newfreq = spear_cpufreq.freq_tbl[index].frequency * 1000;

	if (of_machine_is_compatible("st,spear1340")) {
		/*
		 * SPEAr1340 is special in the sense that due to the possibility
		 * of multiple clock sources for cpu clk's parent we can have
		 * different clock source for different frequency of cpu clk.
		 * Hence we need to choose one from amongst these possible clock
		 * sources.
		 */
		srcclk = spear1340_cpu_get_possible_parent(newfreq);
		if (IS_ERR(srcclk)) {
			pr_err("Failed to get src clk\n");
			return PTR_ERR(srcclk);
		}

		/* SPEAr1340: src clk is always 2 * intended cpu clk */
		mult = 2;
	} else {
		/*
		 * src clock to be altered is ancestor of cpu clock. Hence we
		 * can directly work on cpu clk
		 */
		srcclk = spear_cpufreq.clk;
	}

	newfreq = clk_round_rate(srcclk, newfreq * mult);
	if (newfreq <= 0) {
		pr_err("clk_round_rate failed for cpu src clock\n");
		return newfreq;
	}

	if (mult == 2)
		ret = spear1340_set_cpu_rate(srcclk, newfreq);
	else
		ret = clk_set_rate(spear_cpufreq.clk, newfreq);

	if (ret)
		pr_err("CPU Freq: cpu clk_set_rate failed: %d\n", ret);

	return ret;
}