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
struct pmc_mdep {int /*<<< orphan*/  pmd_intr; int /*<<< orphan*/  pmd_npmc; struct pmc_classdep* pmd_classdep; int /*<<< orphan*/  pmd_cputype; } ;
struct pmc_classdep {int pcd_width; int /*<<< orphan*/  pcd_write_pmc; int /*<<< orphan*/  pcd_stop_pmc; int /*<<< orphan*/  pcd_start_pmc; int /*<<< orphan*/  pcd_release_pmc; int /*<<< orphan*/  pcd_read_pmc; int /*<<< orphan*/  pcd_get_config; int /*<<< orphan*/  pcd_describe; int /*<<< orphan*/  pcd_pcpu_init; int /*<<< orphan*/  pcd_pcpu_fini; int /*<<< orphan*/  pcd_config_pmc; int /*<<< orphan*/  pcd_allocate_pmc; int /*<<< orphan*/  pcd_ri; scalar_t__ pcd_num; int /*<<< orphan*/  pcd_class; int /*<<< orphan*/  pcd_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CLASS_PPC970 ; 
 int /*<<< orphan*/  PMC_CPU_PPC_970 ; 
 size_t PMC_MDEP_CLASS_INDEX_POWERPC ; 
 int /*<<< orphan*/  POWERPC_PMC_CAPS ; 
 scalar_t__ PPC970_MAX_PMCS ; 
 int /*<<< orphan*/  powerpc_describe ; 
 int /*<<< orphan*/  powerpc_get_config ; 
 int /*<<< orphan*/  ppc970_allocate_pmc ; 
 int /*<<< orphan*/  ppc970_config_pmc ; 
 int /*<<< orphan*/  ppc970_intr ; 
 int /*<<< orphan*/  ppc970_pcpu_fini ; 
 int /*<<< orphan*/  ppc970_pcpu_init ; 
 int /*<<< orphan*/  ppc970_read_pmc ; 
 int /*<<< orphan*/  ppc970_release_pmc ; 
 int /*<<< orphan*/  ppc970_start_pmc ; 
 int /*<<< orphan*/  ppc970_stop_pmc ; 
 int /*<<< orphan*/  ppc970_write_pmc ; 

int
pmc_ppc970_initialize(struct pmc_mdep *pmc_mdep)
{
	struct pmc_classdep *pcd;
	
	pmc_mdep->pmd_cputype = PMC_CPU_PPC_970;

	pcd = &pmc_mdep->pmd_classdep[PMC_MDEP_CLASS_INDEX_POWERPC];
	pcd->pcd_caps  = POWERPC_PMC_CAPS;
	pcd->pcd_class = PMC_CLASS_PPC970;
	pcd->pcd_num   = PPC970_MAX_PMCS;
	pcd->pcd_ri    = pmc_mdep->pmd_npmc;
	pcd->pcd_width = 32;

	pcd->pcd_allocate_pmc   = ppc970_allocate_pmc;
	pcd->pcd_config_pmc     = ppc970_config_pmc;
	pcd->pcd_pcpu_fini      = ppc970_pcpu_fini;
	pcd->pcd_pcpu_init      = ppc970_pcpu_init;
	pcd->pcd_describe       = powerpc_describe;
	pcd->pcd_get_config     = powerpc_get_config;
	pcd->pcd_read_pmc       = ppc970_read_pmc;
	pcd->pcd_release_pmc    = ppc970_release_pmc;
	pcd->pcd_start_pmc      = ppc970_start_pmc;
	pcd->pcd_stop_pmc       = ppc970_stop_pmc;
 	pcd->pcd_write_pmc      = ppc970_write_pmc;

	pmc_mdep->pmd_npmc     += PPC970_MAX_PMCS;
	pmc_mdep->pmd_intr      = ppc970_intr;

	return (0);
}