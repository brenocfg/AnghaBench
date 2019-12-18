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
struct cpufreq_policy {int /*<<< orphan*/  stats; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_stats_clear_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_reset(struct cpufreq_policy *policy, const char *buf,
			   size_t count)
{
	/* We don't care what is written to the attribute. */
	cpufreq_stats_clear_table(policy->stats);
	return count;
}