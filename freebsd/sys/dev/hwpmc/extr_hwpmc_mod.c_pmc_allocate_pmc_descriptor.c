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
struct pmc_pcpu_state {int dummy; } ;
struct pmc {void* pm_pcpu_state; int /*<<< orphan*/  pm_runcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PMC ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*) ; 
 int /*<<< orphan*/  counter_u64_alloc (int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 

__attribute__((used)) static struct pmc *
pmc_allocate_pmc_descriptor(void)
{
	struct pmc *pmc;

	pmc = malloc(sizeof(struct pmc), M_PMC, M_WAITOK|M_ZERO);
	pmc->pm_runcount = counter_u64_alloc(M_WAITOK);
	pmc->pm_pcpu_state = malloc(sizeof(struct pmc_pcpu_state)*mp_ncpus, M_PMC, M_WAITOK|M_ZERO);
	PMCDBG1(PMC,ALL,1, "allocate-pmc -> pmc=%p", pmc);

	return pmc;
}