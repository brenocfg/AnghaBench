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
struct pmc_mdep {int dummy; } ;

/* Variables and functions */
 int ARMV7_PMNC_ENABLE ; 
 int /*<<< orphan*/  cp15_pmcnten_clr (int) ; 
 int cp15_pmcr_get () ; 
 int /*<<< orphan*/  cp15_pmcr_set (int) ; 
 int /*<<< orphan*/  cp15_pminten_clr (int) ; 
 int /*<<< orphan*/  cp15_pmovsr_set (int) ; 

__attribute__((used)) static int
armv7_pcpu_fini(struct pmc_mdep *md, int cpu)
{
	uint32_t pmnc;

	pmnc = cp15_pmcr_get();
	pmnc &= ~ARMV7_PMNC_ENABLE;
	cp15_pmcr_set(pmnc);

	pmnc = 0xffffffff;
	cp15_pmcnten_clr(pmnc);
	cp15_pminten_clr(pmnc);
	cp15_pmovsr_set(pmnc);

	return 0;
}