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
struct cs_dbs_tuners {int freq_step; } ;
struct cpufreq_policy {int max; } ;

/* Variables and functions */
 unsigned int DEF_FREQUENCY_STEP ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned int get_freq_step(struct cs_dbs_tuners *cs_tuners,
					 struct cpufreq_policy *policy)
{
	unsigned int freq_step = (cs_tuners->freq_step * policy->max) / 100;

	/* max freq cannot be less than 100. But who knows... */
	if (unlikely(freq_step == 0))
		freq_step = DEF_FREQUENCY_STEP;

	return freq_step;
}