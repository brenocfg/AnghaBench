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
struct cpufreq_policy {unsigned int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __us2e_freq_target ; 
 int smp_call_function_single (unsigned int,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int us2e_freq_target(struct cpufreq_policy *policy, unsigned int index)
{
	unsigned int cpu = policy->cpu;

	return smp_call_function_single(cpu, __us2e_freq_target, &index, 1);
}