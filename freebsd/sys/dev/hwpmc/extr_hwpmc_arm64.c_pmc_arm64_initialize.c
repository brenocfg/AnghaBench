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
struct pmc_mdep {int pmd_npmc; int /*<<< orphan*/  pmd_switch_out; int /*<<< orphan*/  pmd_switch_in; int /*<<< orphan*/  pmd_intr; struct pmc_classdep* pmd_classdep; int /*<<< orphan*/  pmd_cputype; } ;
struct pmc_classdep {int pcd_num; int pcd_ri; int pcd_width; int /*<<< orphan*/  pcd_write_pmc; int /*<<< orphan*/  pcd_stop_pmc; int /*<<< orphan*/  pcd_start_pmc; int /*<<< orphan*/  pcd_release_pmc; int /*<<< orphan*/  pcd_read_pmc; int /*<<< orphan*/  pcd_get_config; int /*<<< orphan*/  pcd_describe; int /*<<< orphan*/  pcd_pcpu_init; int /*<<< orphan*/  pcd_pcpu_fini; int /*<<< orphan*/  pcd_config_pmc; int /*<<< orphan*/  pcd_allocate_pmc; int /*<<< orphan*/  pcd_class; int /*<<< orphan*/  pcd_caps; } ;
struct arm64_cpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMV8_PMC_CAPS ; 
 int /*<<< orphan*/  INI ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
#define  PMCR_IDCODE_CORTEX_A53 130 
#define  PMCR_IDCODE_CORTEX_A57 129 
#define  PMCR_IDCODE_CORTEX_A72 128 
 int PMCR_IDCODE_MASK ; 
 int PMCR_IDCODE_SHIFT ; 
 int PMCR_N_MASK ; 
 int PMCR_N_SHIFT ; 
 int /*<<< orphan*/  PMC_CLASS_ARMV8 ; 
 int /*<<< orphan*/  PMC_CPU_ARMV8_CORTEX_A53 ; 
 int /*<<< orphan*/  PMC_CPU_ARMV8_CORTEX_A57 ; 
 size_t PMC_MDEP_CLASS_INDEX_ARMV8 ; 
 int /*<<< orphan*/  arm64_allocate_pmc ; 
 int /*<<< orphan*/  arm64_config_pmc ; 
 int /*<<< orphan*/  arm64_describe ; 
 int /*<<< orphan*/  arm64_get_config ; 
 int /*<<< orphan*/  arm64_intr ; 
 int arm64_npmcs ; 
 int /*<<< orphan*/  arm64_pcpu ; 
 int /*<<< orphan*/  arm64_pcpu_fini ; 
 int /*<<< orphan*/  arm64_pcpu_init ; 
 int arm64_pmcr_read () ; 
 int /*<<< orphan*/  arm64_read_pmc ; 
 int /*<<< orphan*/  arm64_release_pmc ; 
 int /*<<< orphan*/  arm64_start_pmc ; 
 int /*<<< orphan*/  arm64_stop_pmc ; 
 int /*<<< orphan*/  arm64_switch_in ; 
 int /*<<< orphan*/  arm64_switch_out ; 
 int /*<<< orphan*/  arm64_write_pmc ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int pmc_cpu_max () ; 
 struct pmc_mdep* pmc_mdep_alloc (int) ; 

struct pmc_mdep *
pmc_arm64_initialize()
{
	struct pmc_mdep *pmc_mdep;
	struct pmc_classdep *pcd;
	int idcode;
	int reg;

	reg = arm64_pmcr_read();
	arm64_npmcs = (reg & PMCR_N_MASK) >> PMCR_N_SHIFT;
	idcode = (reg & PMCR_IDCODE_MASK) >> PMCR_IDCODE_SHIFT;

	PMCDBG1(MDP, INI, 1, "arm64-init npmcs=%d", arm64_npmcs);

	/*
	 * Allocate space for pointers to PMC HW descriptors and for
	 * the MDEP structure used by MI code.
	 */
	arm64_pcpu = malloc(sizeof(struct arm64_cpu *) * pmc_cpu_max(),
		M_PMC, M_WAITOK | M_ZERO);

	/* Just one class */
	pmc_mdep = pmc_mdep_alloc(1);

	switch (idcode) {
	case PMCR_IDCODE_CORTEX_A57:
	case PMCR_IDCODE_CORTEX_A72:
		pmc_mdep->pmd_cputype = PMC_CPU_ARMV8_CORTEX_A57;
		break;
	default:
	case PMCR_IDCODE_CORTEX_A53:
		pmc_mdep->pmd_cputype = PMC_CPU_ARMV8_CORTEX_A53;
		break;
	}

	pcd = &pmc_mdep->pmd_classdep[PMC_MDEP_CLASS_INDEX_ARMV8];
	pcd->pcd_caps  = ARMV8_PMC_CAPS;
	pcd->pcd_class = PMC_CLASS_ARMV8;
	pcd->pcd_num   = arm64_npmcs;
	pcd->pcd_ri    = pmc_mdep->pmd_npmc;
	pcd->pcd_width = 32;

	pcd->pcd_allocate_pmc   = arm64_allocate_pmc;
	pcd->pcd_config_pmc     = arm64_config_pmc;
	pcd->pcd_pcpu_fini      = arm64_pcpu_fini;
	pcd->pcd_pcpu_init      = arm64_pcpu_init;
	pcd->pcd_describe       = arm64_describe;
	pcd->pcd_get_config     = arm64_get_config;
	pcd->pcd_read_pmc       = arm64_read_pmc;
	pcd->pcd_release_pmc    = arm64_release_pmc;
	pcd->pcd_start_pmc      = arm64_start_pmc;
	pcd->pcd_stop_pmc       = arm64_stop_pmc;
	pcd->pcd_write_pmc      = arm64_write_pmc;

	pmc_mdep->pmd_intr       = arm64_intr;
	pmc_mdep->pmd_switch_in  = arm64_switch_in;
	pmc_mdep->pmd_switch_out = arm64_switch_out;

	pmc_mdep->pmd_npmc   += arm64_npmcs;

	return (pmc_mdep);
}