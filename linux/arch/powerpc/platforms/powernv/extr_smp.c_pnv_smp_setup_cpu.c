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
 int PPC_BIT (int) ; 
 int /*<<< orphan*/  PVR_POWER9 ; 
 int /*<<< orphan*/  SPRN_HMEER ; 
 int boot_cpuid ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pvr_version_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xics_setup_cpu () ; 
 scalar_t__ xive_enabled () ; 
 int /*<<< orphan*/  xive_smp_setup_cpu () ; 

__attribute__((used)) static void pnv_smp_setup_cpu(int cpu)
{
	/*
	 * P9 workaround for CI vector load (see traps.c),
	 * enable the corresponding HMI interrupt
	 */
	if (pvr_version_is(PVR_POWER9))
		mtspr(SPRN_HMEER, mfspr(SPRN_HMEER) | PPC_BIT(17));

	if (xive_enabled())
		xive_smp_setup_cpu();
	else if (cpu != boot_cpuid)
		xics_setup_cpu();
}