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
struct cpuref {int /*<<< orphan*/  cr_cpuid; int /*<<< orphan*/  cr_hwref; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPR_PIR ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpc85xx_smp_get_bsp(platform_t plat, struct cpuref *cpuref)
{

	cpuref->cr_cpuid = mfspr(SPR_PIR);
	cpuref->cr_hwref = cpuref->cr_cpuid;

	return (0);
}