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
struct cpumask {int dummy; } ;
struct cpufreq_policy {struct acpi_cpufreq_data* driver_data; } ;
struct acpi_cpufreq_data {int dummy; } ;

/* Variables and functions */
 unsigned int extract_freq (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cur_val (struct cpumask const*,struct acpi_cpufreq_data*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int check_freqs(struct cpufreq_policy *policy,
				const struct cpumask *mask, unsigned int freq)
{
	struct acpi_cpufreq_data *data = policy->driver_data;
	unsigned int cur_freq;
	unsigned int i;

	for (i = 0; i < 100; i++) {
		cur_freq = extract_freq(policy, get_cur_val(mask, data));
		if (cur_freq == freq)
			return 1;
		udelay(10);
	}
	return 0;
}