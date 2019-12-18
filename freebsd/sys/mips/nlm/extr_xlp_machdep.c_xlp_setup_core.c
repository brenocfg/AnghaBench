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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LSU_DEFEATURE ; 
 int /*<<< orphan*/  SCHED_DEFEATURE ; 
 int nlm_mfcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_mtcr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xlp_setup_core(void)
{
	uint64_t reg;

	reg = nlm_mfcr(LSU_DEFEATURE);
	/* Enable Unaligned and L2HPE */
	reg |= (1 << 30) | (1 << 23);
	/*
	 * Experimental : Enable SUE
	 * Speculative Unmap Enable. Enable speculative L2 cache request for
	 * unmapped access.
	 */
	reg |= (1ull << 31);
	/* Clear S1RCM  - A0 errata */
	reg &= ~0xeull;
	nlm_mtcr(LSU_DEFEATURE, reg);

	reg = nlm_mfcr(SCHED_DEFEATURE);
	/* Experimental: Disable BRU accepting ALU ops - A0 errata */
	reg |= (1 << 24);
	nlm_mtcr(SCHED_DEFEATURE, reg);
}