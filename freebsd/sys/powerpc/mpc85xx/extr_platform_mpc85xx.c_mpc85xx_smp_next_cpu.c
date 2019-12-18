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
struct cpuref {int cr_cpuid; int cr_hwref; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ bootverbose ; 
 scalar_t__ cpu ; 
 scalar_t__ maxcpu ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
mpc85xx_smp_next_cpu(platform_t plat, struct cpuref *cpuref)
{

	if (cpu >= maxcpu)
		return (ENOENT);

	cpuref->cr_cpuid = cpu++;
	cpuref->cr_hwref = cpuref->cr_cpuid;
	if (bootverbose)
		printf("powerpc_smp_next_cpu: cpuid %d\n", cpuref->cr_cpuid);

	return (0);
}