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
 void MMU_CPU_BOOTSTRAP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmu_obj ; 

void
pmap_cpu_bootstrap(int ap)
{
	/*
	 * No KTR here because our console probably doesn't work yet
	 */

	return (MMU_CPU_BOOTSTRAP(mmu_obj, ap));
}