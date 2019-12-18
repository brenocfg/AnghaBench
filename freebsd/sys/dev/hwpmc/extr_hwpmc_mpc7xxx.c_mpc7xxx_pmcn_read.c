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
typedef  int /*<<< orphan*/  pmc_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPR_PMC1 ; 
 int /*<<< orphan*/  SPR_PMC2 ; 
 int /*<<< orphan*/  SPR_PMC3 ; 
 int /*<<< orphan*/  SPR_PMC4 ; 
 int /*<<< orphan*/  SPR_PMC5 ; 
 int /*<<< orphan*/  SPR_PMC6 ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

__attribute__((used)) static pmc_value_t
mpc7xxx_pmcn_read(unsigned int pmc)
{
	switch (pmc) {
		case 0:
			return mfspr(SPR_PMC1);
			break;
		case 1:
			return mfspr(SPR_PMC2);
			break;
		case 2:
			return mfspr(SPR_PMC3);
			break;
		case 3:
			return mfspr(SPR_PMC4);
			break;
		case 4:
			return mfspr(SPR_PMC5);
			break;
		case 5:
			return mfspr(SPR_PMC6);
		default:
			panic("Invalid PMC number: %d\n", pmc);
	}
}