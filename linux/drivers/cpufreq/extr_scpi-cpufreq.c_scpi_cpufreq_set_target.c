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
typedef  scalar_t__ u64 ;
struct scpi_data {int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; int /*<<< orphan*/  related_cpus; struct scpi_data* driver_data; TYPE_2__* freq_table; } ;
struct TYPE_4__ {unsigned long frequency; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  arch_set_freq_scale (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
scpi_cpufreq_set_target(struct cpufreq_policy *policy, unsigned int index)
{
	unsigned long freq = policy->freq_table[index].frequency;
	struct scpi_data *priv = policy->driver_data;
	u64 rate = freq * 1000;
	int ret;

	ret = clk_set_rate(priv->clk, rate);

	if (ret)
		return ret;

	if (clk_get_rate(priv->clk) != rate)
		return -EIO;

	arch_set_freq_scale(policy->related_cpus, freq,
			    policy->cpuinfo.max_freq);

	return 0;
}