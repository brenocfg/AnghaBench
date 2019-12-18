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

/* Variables and functions */
 unsigned int NSEC_PER_USEC ; 
 unsigned int cppc_get_transition_latency (int) ; 

__attribute__((used)) static unsigned int cppc_cpufreq_get_transition_delay_us(int cpu)
{
	return cppc_get_transition_latency(cpu) / NSEC_PER_USEC;
}