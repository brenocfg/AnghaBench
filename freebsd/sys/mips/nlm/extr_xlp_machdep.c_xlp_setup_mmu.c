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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int mips_rd_pagegrain () ; 
 int /*<<< orphan*/  mips_wr_pagegrain (unsigned int) ; 
 int /*<<< orphan*/  nlm_extended_tlb_en (int) ; 
 int /*<<< orphan*/  nlm_large_variable_tlb_en (int) ; 
 int /*<<< orphan*/  nlm_mmu_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_extended_pagemask (int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_threadid () ; 

__attribute__((used)) static void
xlp_setup_mmu(void)
{
	uint32_t pagegrain;

	if (nlm_threadid() == 0) {
		nlm_setup_extended_pagemask(0);
		nlm_large_variable_tlb_en(1);
		nlm_extended_tlb_en(1);
		nlm_mmu_setup(0, 0, 0);
	}

	/* Enable no-read, no-exec, large-physical-address */
	pagegrain = mips_rd_pagegrain();
	pagegrain |= (1U << 31)	|	/* RIE */
	    (1 << 30)		|	/* XIE */
	    (1 << 29);			/* ELPA */
	mips_wr_pagegrain(pagegrain);
}