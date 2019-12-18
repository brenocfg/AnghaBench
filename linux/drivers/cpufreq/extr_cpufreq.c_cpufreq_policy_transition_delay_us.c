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
struct TYPE_2__ {unsigned int transition_latency; } ;
struct cpufreq_policy {unsigned int transition_delay_us; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 unsigned int LATENCY_MULTIPLIER ; 
 unsigned int NSEC_PER_USEC ; 
 unsigned int min (unsigned int,unsigned int) ; 

unsigned int cpufreq_policy_transition_delay_us(struct cpufreq_policy *policy)
{
	unsigned int latency;

	if (policy->transition_delay_us)
		return policy->transition_delay_us;

	latency = policy->cpuinfo.transition_latency / NSEC_PER_USEC;
	if (latency) {
		/*
		 * For platforms that can change the frequency very fast (< 10
		 * us), the above formula gives a decent transition delay. But
		 * for platforms where transition_latency is in milliseconds, it
		 * ends up giving unrealistic values.
		 *
		 * Cap the default transition delay to 10 ms, which seems to be
		 * a reasonable amount of time after which we should reevaluate
		 * the frequency.
		 */
		return min(latency * LATENCY_MULTIPLIER, (unsigned int)10000);
	}

	return LATENCY_MULTIPLIER;
}