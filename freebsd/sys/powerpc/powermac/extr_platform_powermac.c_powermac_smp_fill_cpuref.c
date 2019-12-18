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
struct cpuref {int cr_cpuid; int /*<<< orphan*/  cr_hwref; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  cpuid ;
typedef  int cell_t ;

/* Variables and functions */
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 

__attribute__((used)) static int
powermac_smp_fill_cpuref(struct cpuref *cpuref, phandle_t cpu)
{
	cell_t cpuid;
	int res;

	cpuref->cr_hwref = cpu;
	res = OF_getprop(cpu, "reg", &cpuid, sizeof(cpuid));

	/*
	 * psim doesn't have a reg property, so assume 0 as for the
	 * uniprocessor case in the CHRP spec. 
	 */
	if (res < 0) {
		cpuid = 0;
	}

	cpuref->cr_cpuid = cpuid & 0xff;
	return (0);
}