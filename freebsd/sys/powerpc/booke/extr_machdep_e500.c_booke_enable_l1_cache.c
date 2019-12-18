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

/* Variables and functions */
 int L1CSR0_DCE ; 
 int L1CSR1_ICE ; 
 int RB_VERBOSE ; 
 int /*<<< orphan*/  SPR_L1CSR0 ; 
 int /*<<< orphan*/  SPR_L1CSR1 ; 
 int boothowto ; 
 int /*<<< orphan*/  dcache_enable () ; 
 int /*<<< orphan*/  dcache_inval () ; 
 int /*<<< orphan*/  icache_enable () ; 
 int /*<<< orphan*/  icache_inval () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
booke_enable_l1_cache(void)
{
	uint32_t csr;

	/* Enable D-cache if applicable */
	csr = mfspr(SPR_L1CSR0);
	if ((csr & L1CSR0_DCE) == 0) {
		dcache_inval();
		dcache_enable();
	}

	csr = mfspr(SPR_L1CSR0);
	if ((boothowto & RB_VERBOSE) != 0 || (csr & L1CSR0_DCE) == 0)
		printf("L1 D-cache %sabled\n",
		    (csr & L1CSR0_DCE) ? "en" : "dis");

	/* Enable L1 I-cache if applicable. */
	csr = mfspr(SPR_L1CSR1);
	if ((csr & L1CSR1_ICE) == 0) {
		icache_inval();
		icache_enable();
	}

	csr = mfspr(SPR_L1CSR1);
	if ((boothowto & RB_VERBOSE) != 0 || (csr & L1CSR1_ICE) == 0)
		printf("L1 I-cache %sabled\n",
		    (csr & L1CSR1_ICE) ? "en" : "dis");
}