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
struct cpuref {int /*<<< orphan*/  cr_cpuid; } ;

/* Variables and functions */
 scalar_t__ max (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mp_maxid ; 
 int mp_ncpus ; 
 int platform_smp_first_cpu (struct cpuref*) ; 
 int platform_smp_next_cpu (struct cpuref*) ; 

void
cpu_mp_setmaxid(void)
{
	struct cpuref cpuref;
	int error;

	mp_ncpus = 0;
	mp_maxid = 0;
	error = platform_smp_first_cpu(&cpuref);
	while (!error) {
		mp_ncpus++;
		mp_maxid = max(cpuref.cr_cpuid, mp_maxid);
		error = platform_smp_next_cpu(&cpuref);
	}
	/* Sanity. */
	if (mp_ncpus == 0)
		mp_ncpus = 1;
}