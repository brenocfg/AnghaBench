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
 int /*<<< orphan*/  SPR_PMC1 ; 
 int /*<<< orphan*/  SPR_PMC2 ; 
 int /*<<< orphan*/  SPR_PMC3 ; 
 int /*<<< orphan*/  SPR_PMC4 ; 
 int /*<<< orphan*/  SPR_PMC5 ; 
 int /*<<< orphan*/  SPR_PMC6 ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

__attribute__((used)) static void
mpc7xxx_pmcn_write(unsigned int pmc, uint32_t val)
{
	switch (pmc) {
		case 0:
			mtspr(SPR_PMC1, val);
			break;
		case 1:
			mtspr(SPR_PMC2, val);
			break;
		case 2:
			mtspr(SPR_PMC3, val);
			break;
		case 3:
			mtspr(SPR_PMC4, val);
			break;
		case 4:
			mtspr(SPR_PMC5, val);
			break;
		case 5:
			mtspr(SPR_PMC6, val);
			break;
		default:
			panic("Invalid PMC number: %d\n", pmc);
	}
}