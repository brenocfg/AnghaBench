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
struct cpufreq_policy {int dummy; } ;
struct cpufreq_frequency_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIPS_CPUFREQ_NAME ; 
 scalar_t__ IS_ERR (struct cpufreq_frequency_table*) ; 
 int PTR_ERR (struct cpufreq_frequency_table*) ; 
 int /*<<< orphan*/  TRANSITION_LATENCY ; 
 struct cpufreq_frequency_table* bmips_cpufreq_get_freq_table (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_generic_init (struct cpufreq_policy*,struct cpufreq_frequency_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmips_cpufreq_init(struct cpufreq_policy *policy)
{
	struct cpufreq_frequency_table *freq_table;

	freq_table = bmips_cpufreq_get_freq_table(policy);
	if (IS_ERR(freq_table)) {
		pr_err("%s: couldn't determine frequency table (%ld).\n",
			BMIPS_CPUFREQ_NAME, PTR_ERR(freq_table));
		return PTR_ERR(freq_table);
	}

	cpufreq_generic_init(policy, freq_table, TRANSITION_LATENCY);
	pr_info("%s: registered\n", BMIPS_CPUFREQ_NAME);

	return 0;
}