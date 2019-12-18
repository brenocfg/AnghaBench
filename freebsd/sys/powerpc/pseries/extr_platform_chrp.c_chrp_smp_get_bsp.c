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
struct cpuref {int /*<<< orphan*/  cr_hwref; int /*<<< orphan*/  cr_cpuid; } ;
typedef  int /*<<< orphan*/  platform_t ;
struct TYPE_2__ {int /*<<< orphan*/  cr_hwref; int /*<<< orphan*/  cr_cpuid; } ;

/* Variables and functions */
 TYPE_1__* platform_cpuref ; 

__attribute__((used)) static int
chrp_smp_get_bsp(platform_t plat, struct cpuref *cpuref)
{

	cpuref->cr_cpuid = platform_cpuref[0].cr_cpuid;
	cpuref->cr_hwref = platform_cpuref[0].cr_hwref;
	return (0);
}