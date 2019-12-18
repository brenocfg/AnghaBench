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
 int /*<<< orphan*/  SPR_970PMC1 ; 
 int /*<<< orphan*/  SPR_970PMC2 ; 
 int /*<<< orphan*/  SPR_970PMC3 ; 
 int /*<<< orphan*/  SPR_970PMC4 ; 
 int /*<<< orphan*/  SPR_970PMC5 ; 
 int /*<<< orphan*/  SPR_970PMC6 ; 
 int /*<<< orphan*/  SPR_970PMC7 ; 
 int /*<<< orphan*/  SPR_970PMC8 ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

__attribute__((used)) static pmc_value_t
ppc970_pmcn_read(unsigned int pmc)
{
	pmc_value_t val;

	switch (pmc) {
		case 0:
			val = mfspr(SPR_970PMC1);
			break;
		case 1:
			val = mfspr(SPR_970PMC2);
			break;
		case 2:
			val = mfspr(SPR_970PMC3);
			break;
		case 3:
			val = mfspr(SPR_970PMC4);
			break;
		case 4:
			val = mfspr(SPR_970PMC5);
			break;
		case 5:
			val = mfspr(SPR_970PMC6);
			break;
		case 6:
			val = mfspr(SPR_970PMC7);
			break;
		case 7:
			val = mfspr(SPR_970PMC8);
			break;
		default:
			panic("Invalid PMC number: %d\n", pmc);
	}

	return (val);
}