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
 int BUCSR_BPEN ; 
 int RB_VERBOSE ; 
 int /*<<< orphan*/  SPR_BUCSR ; 
 int boothowto ; 
 int /*<<< orphan*/  bpred_enable () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
booke_enable_bpred(void)
{
	uint32_t csr;

	bpred_enable();
	csr = mfspr(SPR_BUCSR);
	if ((boothowto & RB_VERBOSE) != 0 || (csr & BUCSR_BPEN) == 0)
		printf("Branch Predictor %sabled\n",
		    (csr & BUCSR_BPEN) ? "en" : "dis");
}