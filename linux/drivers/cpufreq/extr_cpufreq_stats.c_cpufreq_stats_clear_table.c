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
typedef  int /*<<< orphan*/  u64 ;
struct cpufreq_stats {unsigned int max_state; int /*<<< orphan*/  lock; scalar_t__ total_trans; int /*<<< orphan*/  last_time; int /*<<< orphan*/  trans_table; int /*<<< orphan*/  time_in_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpufreq_stats_clear_table(struct cpufreq_stats *stats)
{
	unsigned int count = stats->max_state;

	spin_lock(&stats->lock);
	memset(stats->time_in_state, 0, count * sizeof(u64));
	memset(stats->trans_table, 0, count * count * sizeof(int));
	stats->last_time = get_jiffies_64();
	stats->total_trans = 0;
	spin_unlock(&stats->lock);
}