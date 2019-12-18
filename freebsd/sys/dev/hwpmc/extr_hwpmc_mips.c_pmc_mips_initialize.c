#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmc_mdep {int pmd_npmc; int /*<<< orphan*/  pmd_switch_out; int /*<<< orphan*/  pmd_switch_in; int /*<<< orphan*/  pmd_intr; struct pmc_classdep* pmd_classdep; int /*<<< orphan*/  pmd_cputype; } ;
struct pmc_classdep {int pcd_num; int pcd_ri; int /*<<< orphan*/  pcd_write_pmc; int /*<<< orphan*/  pcd_stop_pmc; int /*<<< orphan*/  pcd_start_pmc; int /*<<< orphan*/  pcd_release_pmc; int /*<<< orphan*/  pcd_read_pmc; int /*<<< orphan*/  pcd_get_config; int /*<<< orphan*/  pcd_describe; int /*<<< orphan*/  pcd_pcpu_init; int /*<<< orphan*/  pcd_pcpu_fini; int /*<<< orphan*/  pcd_config_pmc; int /*<<< orphan*/  pcd_allocate_pmc; int /*<<< orphan*/  pcd_width; int /*<<< orphan*/  pcd_class; int /*<<< orphan*/  pcd_caps; } ;
struct mips_cpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ps_counter_width; int /*<<< orphan*/  ps_cpuclass; int /*<<< orphan*/  ps_capabilities; int /*<<< orphan*/  ps_cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  INI ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 size_t PMC_MDEP_CLASS_INDEX_MIPS ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mips_allocate_pmc ; 
 int /*<<< orphan*/  mips_config_pmc ; 
 int /*<<< orphan*/  mips_describe ; 
 int /*<<< orphan*/  mips_get_config ; 
 int mips_npmcs ; 
 int /*<<< orphan*/  mips_pcpu ; 
 int /*<<< orphan*/  mips_pcpu_fini ; 
 int /*<<< orphan*/  mips_pcpu_init ; 
 int /*<<< orphan*/  mips_pmc_intr ; 
 TYPE_1__ mips_pmc_spec ; 
 int /*<<< orphan*/  mips_pmc_switch_in ; 
 int /*<<< orphan*/  mips_pmc_switch_out ; 
 int /*<<< orphan*/  mips_read_pmc ; 
 int /*<<< orphan*/  mips_release_pmc ; 
 int /*<<< orphan*/  mips_start_pmc ; 
 int /*<<< orphan*/  mips_stop_pmc ; 
 int /*<<< orphan*/  mips_write_pmc ; 
 int pmc_cpu_max () ; 
 struct pmc_mdep* pmc_mdep_alloc (int) ; 

struct pmc_mdep *
pmc_mips_initialize()
{
	struct pmc_mdep *pmc_mdep;
	struct pmc_classdep *pcd;
	
	/*
	 * TODO: Use More bit of PerfCntlX register to detect actual 
	 * number of counters
	 */
	mips_npmcs = 2;
	
	PMCDBG1(MDP,INI,1,"mips-init npmcs=%d", mips_npmcs);

	/*
	 * Allocate space for pointers to PMC HW descriptors and for
	 * the MDEP structure used by MI code.
	 */
	mips_pcpu = malloc(sizeof(struct mips_cpu *) * pmc_cpu_max(), M_PMC,
			   M_WAITOK|M_ZERO);

	/* Just one class */
	pmc_mdep = pmc_mdep_alloc(1);

	pmc_mdep->pmd_cputype = mips_pmc_spec.ps_cputype;

	pcd = &pmc_mdep->pmd_classdep[PMC_MDEP_CLASS_INDEX_MIPS];
	pcd->pcd_caps  = mips_pmc_spec.ps_capabilities;
	pcd->pcd_class = mips_pmc_spec.ps_cpuclass;
	pcd->pcd_num   = mips_npmcs;
	pcd->pcd_ri    = pmc_mdep->pmd_npmc;
	pcd->pcd_width = mips_pmc_spec.ps_counter_width;

	pcd->pcd_allocate_pmc   = mips_allocate_pmc;
	pcd->pcd_config_pmc     = mips_config_pmc;
	pcd->pcd_pcpu_fini      = mips_pcpu_fini;
	pcd->pcd_pcpu_init      = mips_pcpu_init;
	pcd->pcd_describe       = mips_describe;
	pcd->pcd_get_config	= mips_get_config;
	pcd->pcd_read_pmc       = mips_read_pmc;
	pcd->pcd_release_pmc    = mips_release_pmc;
	pcd->pcd_start_pmc      = mips_start_pmc;
	pcd->pcd_stop_pmc       = mips_stop_pmc;
 	pcd->pcd_write_pmc      = mips_write_pmc;

	pmc_mdep->pmd_intr       = mips_pmc_intr;
	pmc_mdep->pmd_switch_in  = mips_pmc_switch_in;
	pmc_mdep->pmd_switch_out = mips_pmc_switch_out;
	
	pmc_mdep->pmd_npmc   += mips_npmcs;

	return (pmc_mdep);
}