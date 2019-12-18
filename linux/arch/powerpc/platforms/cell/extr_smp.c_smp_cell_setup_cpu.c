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
 int DABRX_KERNEL ; 
 int DABRX_USER ; 
 int /*<<< orphan*/  SPRN_DABRX ; 
 int boot_cpuid ; 
 int /*<<< orphan*/  iic_setup_cpu () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smp_cell_setup_cpu(int cpu)
{
	if (cpu != boot_cpuid)
		iic_setup_cpu();

	/*
	 * change default DABRX to allow user watchpoints
	 */
	mtspr(SPRN_DABRX, DABRX_KERNEL | DABRX_USER);
}