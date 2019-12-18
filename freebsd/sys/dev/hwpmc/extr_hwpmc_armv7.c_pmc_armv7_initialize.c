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
struct armv7_cpu {int dummy; } ;

/* Variables and functions */
#define  ARMV7_IDCODE_CORTEX_A8 129 
#define  ARMV7_IDCODE_CORTEX_A9 128 
 int ARMV7_IDCODE_MASK ; 
 int ARMV7_IDCODE_SHIFT ; 
 int /*<<< orphan*/  ARMV7_PMC_CAPS ; 
 int ARMV7_PMNC_N_MASK ; 
 int ARMV7_PMNC_N_SHIFT ; 
 int /*<<< orphan*/  INI ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  PMC_CLASS_ARMV7 ; 
 int /*<<< orphan*/  PMC_CPU_ARMV7_CORTEX_A8 ; 
 int /*<<< orphan*/  PMC_CPU_ARMV7_CORTEX_A9 ; 
 size_t PMC_MDEP_CLASS_INDEX_ARMV7 ; 
 int /*<<< orphan*/  armv7_allocate_pmc ; 
 int /*<<< orphan*/  armv7_config_pmc ; 
 int /*<<< orphan*/  armv7_describe ; 
 int /*<<< orphan*/  armv7_get_config ; 
 int /*<<< orphan*/  armv7_intr ; 
 int armv7_npmcs ; 
 int /*<<< orphan*/  armv7_pcpu ; 
 int /*<<< orphan*/  armv7_pcpu_fini ; 
 int /*<<< orphan*/  armv7_pcpu_init ; 
 int /*<<< orphan*/  armv7_read_pmc ; 
 int /*<<< orphan*/  armv7_release_pmc ; 
 int /*<<< orphan*/  armv7_start_pmc ; 
 int /*<<< orphan*/  armv7_stop_pmc ; 
 int /*<<< orphan*/  armv7_switch_in ; 
 int /*<<< orphan*/  armv7_switch_out ; 
 int /*<<< orphan*/  armv7_write_pmc ; 
 int cp15_pmcr_get () ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int pmc_cpu_max () ; 
 struct pmc_mdep* pmc_mdep_alloc (int) ; 

struct pmc_mdep *
pmc_armv7_initialize()
{
	struct pmc_mdep *pmc_mdep;
	struct pmc_classdep *pcd;
	int idcode;
	int reg;

	reg = cp15_pmcr_get();
	armv7_npmcs = (reg >> ARMV7_PMNC_N_SHIFT) & \
				ARMV7_PMNC_N_MASK;
	idcode = (reg & ARMV7_IDCODE_MASK) >> ARMV7_IDCODE_SHIFT;

	PMCDBG1(MDP, INI, 1, "armv7-init npmcs=%d", armv7_npmcs);
	
	/*
	 * Allocate space for pointers to PMC HW descriptors and for
	 * the MDEP structure used by MI code.
	 */
	armv7_pcpu = malloc(sizeof(struct armv7_cpu *) * pmc_cpu_max(),
		M_PMC, M_WAITOK | M_ZERO);

	/* Just one class */
	pmc_mdep = pmc_mdep_alloc(1);

	switch (idcode) {
	case ARMV7_IDCODE_CORTEX_A9:
		pmc_mdep->pmd_cputype = PMC_CPU_ARMV7_CORTEX_A9;
		break;
	default:
	case ARMV7_IDCODE_CORTEX_A8:
		/*
		 * On A8 we implemented common events only,
		 * so use it for the rest of machines.
		 */
		pmc_mdep->pmd_cputype = PMC_CPU_ARMV7_CORTEX_A8;
		break;
	}

	pcd = &pmc_mdep->pmd_classdep[PMC_MDEP_CLASS_INDEX_ARMV7];
	pcd->pcd_caps  = ARMV7_PMC_CAPS;
	pcd->pcd_class = PMC_CLASS_ARMV7;
	pcd->pcd_num   = armv7_npmcs;
	pcd->pcd_ri    = pmc_mdep->pmd_npmc;
	pcd->pcd_width = 32;

	pcd->pcd_allocate_pmc   = armv7_allocate_pmc;
	pcd->pcd_config_pmc     = armv7_config_pmc;
	pcd->pcd_pcpu_fini      = armv7_pcpu_fini;
	pcd->pcd_pcpu_init      = armv7_pcpu_init;
	pcd->pcd_describe       = armv7_describe;
	pcd->pcd_get_config	= armv7_get_config;
	pcd->pcd_read_pmc       = armv7_read_pmc;
	pcd->pcd_release_pmc    = armv7_release_pmc;
	pcd->pcd_start_pmc      = armv7_start_pmc;
	pcd->pcd_stop_pmc       = armv7_stop_pmc;
	pcd->pcd_write_pmc      = armv7_write_pmc;

	pmc_mdep->pmd_intr       = armv7_intr;
	pmc_mdep->pmd_switch_in  = armv7_switch_in;
	pmc_mdep->pmd_switch_out = armv7_switch_out;
	
	pmc_mdep->pmd_npmc   += armv7_npmcs;

	return (pmc_mdep);
}