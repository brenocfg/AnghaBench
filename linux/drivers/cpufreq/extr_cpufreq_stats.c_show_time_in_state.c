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
struct cpufreq_stats {int state_num; int* freq_table; int /*<<< orphan*/ * time_in_state; int /*<<< orphan*/  lock; } ;
struct cpufreq_policy {scalar_t__ fast_switch_enabled; struct cpufreq_stats* stats; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_stats_update (struct cpufreq_stats*) ; 
 scalar_t__ jiffies_64_to_clock_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int,unsigned long long) ; 

__attribute__((used)) static ssize_t show_time_in_state(struct cpufreq_policy *policy, char *buf)
{
	struct cpufreq_stats *stats = policy->stats;
	ssize_t len = 0;
	int i;

	if (policy->fast_switch_enabled)
		return 0;

	spin_lock(&stats->lock);
	cpufreq_stats_update(stats);
	spin_unlock(&stats->lock);

	for (i = 0; i < stats->state_num; i++) {
		len += sprintf(buf + len, "%u %llu\n", stats->freq_table[i],
			(unsigned long long)
			jiffies_64_to_clock_t(stats->time_in_state[i]));
	}
	return len;
}