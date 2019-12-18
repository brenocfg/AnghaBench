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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int MVPCONF0_PVPE_MASK ; 
 int MVPCONF0_PVPE_SHIFT ; 
 int mftc0 (int /*<<< orphan*/ ,int) ; 

void
platform_cpu_mask(cpuset_t *mask)
{
	uint32_t i, ncpus, reg;

	reg = mftc0(0, 2);
	ncpus = ((reg & MVPCONF0_PVPE_MASK) >> MVPCONF0_PVPE_SHIFT) + 1;

	CPU_ZERO(mask);
	for (i = 0; i < ncpus; i++)
		CPU_SET(i, mask);
}