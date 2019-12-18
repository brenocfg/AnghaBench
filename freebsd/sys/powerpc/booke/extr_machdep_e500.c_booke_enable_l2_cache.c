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
 int FSL_E500mc ; 
 int FSL_E5500 ; 
 int L2CSR0_L2E ; 
 int RB_VERBOSE ; 
 int /*<<< orphan*/  SPR_L2CSR0 ; 
 int boothowto ; 
 int /*<<< orphan*/  l2cache_enable () ; 
 int /*<<< orphan*/  l2cache_inval () ; 
 int mfpvr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
booke_enable_l2_cache(void)
{
	uint32_t csr;

	/* Enable L2 cache on E500mc */
	if ((((mfpvr() >> 16) & 0xFFFF) == FSL_E500mc) ||
	    (((mfpvr() >> 16) & 0xFFFF) == FSL_E5500)) {
		csr = mfspr(SPR_L2CSR0);
		if ((csr & L2CSR0_L2E) == 0) {
			l2cache_inval();
			l2cache_enable();
		}

		csr = mfspr(SPR_L2CSR0);
		if ((boothowto & RB_VERBOSE) != 0 || (csr & L2CSR0_L2E) == 0)
			printf("L2 cache %sabled\n",
			    (csr & L2CSR0_L2E) ? "en" : "dis");
	}
}