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
struct cpuref {int /*<<< orphan*/  cr_domain; int /*<<< orphan*/  cr_hwref; scalar_t__ cr_cpuid; } ;
typedef  int /*<<< orphan*/  platform_t ;
struct TYPE_2__ {int /*<<< orphan*/  cr_domain; int /*<<< orphan*/  cr_hwref; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* platform_cpuref ; 
 scalar_t__ platform_cpuref_valid ; 

__attribute__((used)) static int
powernv_smp_first_cpu(platform_t plat, struct cpuref *cpuref)
{
	if (platform_cpuref_valid == 0)
		return (EINVAL);

	cpuref->cr_cpuid = 0;
	cpuref->cr_hwref = platform_cpuref[0].cr_hwref;
	cpuref->cr_domain = platform_cpuref[0].cr_domain;

	return (0);
}