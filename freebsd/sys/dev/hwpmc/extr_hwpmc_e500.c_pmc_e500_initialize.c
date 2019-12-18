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
 scalar_t__ E500_MAX_PMCS ; 
 int /*<<< orphan*/  PMC_CLASS_E500 ; 
 int /*<<< orphan*/  PMC_CPU_PPC_E500 ; 
 size_t PMC_MDEP_CLASS_INDEX_POWERPC ; 
 int /*<<< orphan*/  POWERPC_PMC_CAPS ; 
 int /*<<< orphan*/  e500_allocate_pmc ; 
 int /*<<< orphan*/  e500_config_pmc ; 
 int /*<<< orphan*/  e500_intr ; 
 int /*<<< orphan*/  e500_pcpu_fini ; 
 int /*<<< orphan*/  e500_pcpu_init ; 
 int /*<<< orphan*/  e500_read_pmc ; 
 int /*<<< orphan*/  e500_release_pmc ; 
 int /*<<< orphan*/  e500_start_pmc ; 
 int /*<<< orphan*/  e500_stop_pmc ; 
 int /*<<< orphan*/  e500_write_pmc ; 
 int /*<<< orphan*/  powerpc_describe ; 
 int /*<<< orphan*/  powerpc_get_config ; 

int
pmc_e500_initialize(struct pmc_mdep *pmc_mdep)
{
	struct pmc_classdep *pcd;

	pmc_mdep->pmd_cputype = PMC_CPU_PPC_E500;

	pcd = &pmc_mdep->pmd_classdep[PMC_MDEP_CLASS_INDEX_POWERPC];
	pcd->pcd_caps  = POWERPC_PMC_CAPS;
	pcd->pcd_class = PMC_CLASS_E500;
	pcd->pcd_num   = E500_MAX_PMCS;
	pcd->pcd_ri    = pmc_mdep->pmd_npmc;
	pcd->pcd_width = 32;

	pcd->pcd_allocate_pmc   = e500_allocate_pmc;
	pcd->pcd_config_pmc     = e500_config_pmc;
	pcd->pcd_pcpu_fini      = e500_pcpu_fini;
	pcd->pcd_pcpu_init      = e500_pcpu_init;
	pcd->pcd_describe       = powerpc_describe;
	pcd->pcd_get_config     = powerpc_get_config;
	pcd->pcd_read_pmc       = e500_read_pmc;
	pcd->pcd_release_pmc    = e500_release_pmc;
	pcd->pcd_start_pmc      = e500_start_pmc;
	pcd->pcd_stop_pmc       = e500_stop_pmc;
 	pcd->pcd_write_pmc      = e500_write_pmc;

	pmc_mdep->pmd_npmc   += E500_MAX_PMCS;
	pmc_mdep->pmd_intr   =  e500_intr;

	return (0);
}