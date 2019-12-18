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
 int /*<<< orphan*/  BUS_PROBE_GENERIC ; 
 int /*<<< orphan*/  MMU_TYPE_BOOKE ; 
 int /*<<< orphan*/  PPC_FEATURE_BOOKE ; 
 int PSL_CE ; 
 int PSL_CM ; 
 int PSL_EE ; 
 int PSL_FE0 ; 
 int PSL_FE1 ; 
 int PSL_FP ; 
 int PSL_ME ; 
 int PSL_PR ; 
 int PSL_VEC ; 
 int /*<<< orphan*/  cpu_features ; 
 int /*<<< orphan*/  pmap_mmu_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psl_kernset ; 
 int psl_userset ; 
 int psl_userset32 ; 
 int psl_userstatic ; 

void
booke_cpu_init(void)
{

	cpu_features |= PPC_FEATURE_BOOKE;

	psl_kernset = PSL_CE | PSL_ME | PSL_EE;
#ifdef __powerpc64__
	psl_kernset |= PSL_CM;
#endif
	psl_userset = psl_kernset | PSL_PR;
#ifdef __powerpc64__
	psl_userset32 = psl_userset & ~PSL_CM;
#endif
	psl_userstatic = ~(PSL_VEC | PSL_FP | PSL_FE0 | PSL_FE1);

	pmap_mmu_install(MMU_TYPE_BOOKE, BUS_PROBE_GENERIC);
}