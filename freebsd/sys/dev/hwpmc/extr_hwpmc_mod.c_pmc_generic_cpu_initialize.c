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
struct pmc_mdep {int /*<<< orphan*/  pmd_switch_out; int /*<<< orphan*/  pmd_switch_in; int /*<<< orphan*/ * pmd_pcpu_fini; int /*<<< orphan*/ * pmd_pcpu_init; int /*<<< orphan*/  pmd_cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CPU_GENERIC ; 
 int /*<<< orphan*/  generic_switch_in ; 
 int /*<<< orphan*/  generic_switch_out ; 
 struct pmc_mdep* pmc_mdep_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pmc_mdep *
pmc_generic_cpu_initialize(void)
{
	struct pmc_mdep *md;

	md = pmc_mdep_alloc(0);

	md->pmd_cputype    = PMC_CPU_GENERIC;

	md->pmd_pcpu_init  = NULL;
	md->pmd_pcpu_fini  = NULL;
	md->pmd_switch_in  = generic_switch_in;
	md->pmd_switch_out = generic_switch_out;

	return (md);
}