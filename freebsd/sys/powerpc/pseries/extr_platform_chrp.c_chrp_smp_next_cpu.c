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
struct cpuref {int cr_cpuid; int /*<<< orphan*/  cr_hwref; } ;
typedef  int /*<<< orphan*/  platform_t ;
struct TYPE_2__ {int cr_cpuid; int /*<<< orphan*/  cr_hwref; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 TYPE_1__* platform_cpuref ; 
 int platform_cpuref_cnt ; 
 scalar_t__ platform_cpuref_valid ; 

__attribute__((used)) static int
chrp_smp_next_cpu(platform_t plat, struct cpuref *cpuref)
{
	int id;

	if (platform_cpuref_valid == 0)
		return (EINVAL);

	id = cpuref->cr_cpuid + 1;
	if (id >= platform_cpuref_cnt)
		return (ENOENT);

	cpuref->cr_cpuid = platform_cpuref[id].cr_cpuid;
	cpuref->cr_hwref = platform_cpuref[id].cr_hwref;

	return (0);
}