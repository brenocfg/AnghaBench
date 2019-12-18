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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMR_PMC0 ; 
 int /*<<< orphan*/  PMR_PMC1 ; 
 int /*<<< orphan*/  PMR_PMC2 ; 
 int /*<<< orphan*/  PMR_PMC3 ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

__attribute__((used)) static void
e500_pmcn_write(unsigned int pmc, uint32_t val)
{
	switch (pmc) {
		case 0:
			mtpmr(PMR_PMC0, val);
			break;
		case 1:
			mtpmr(PMR_PMC1, val);
			break;
		case 2:
			mtpmr(PMR_PMC2, val);
			break;
		case 3:
			mtpmr(PMR_PMC3, val);
			break;
		default:
			panic("Invalid PMC number: %d\n", pmc);
	}
}