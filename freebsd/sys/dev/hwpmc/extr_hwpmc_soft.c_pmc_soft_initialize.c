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
struct soft_cpu {int dummy; } ;
struct pmc_mdep {int /*<<< orphan*/  pmd_npmc; struct pmc_classdep* pmd_classdep; } ;
struct pmc_classdep {int pcd_width; int /*<<< orphan*/  pcd_stop_pmc; int /*<<< orphan*/  pcd_start_pmc; int /*<<< orphan*/  pcd_release_pmc; int /*<<< orphan*/  pcd_write_pmc; int /*<<< orphan*/  pcd_read_pmc; int /*<<< orphan*/  pcd_pcpu_fini; int /*<<< orphan*/  pcd_pcpu_init; int /*<<< orphan*/ * pcd_get_msr; int /*<<< orphan*/  pcd_get_config; int /*<<< orphan*/  pcd_describe; int /*<<< orphan*/  pcd_config_pmc; int /*<<< orphan*/  pcd_allocate_pmc; int /*<<< orphan*/  pcd_ri; scalar_t__ pcd_num; int /*<<< orphan*/  pcd_class; int /*<<< orphan*/  pcd_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 size_t PMC_CLASS_INDEX_SOFT ; 
 int /*<<< orphan*/  PMC_CLASS_SOFT ; 
 int /*<<< orphan*/  SOFT_CAPS ; 
 scalar_t__ SOFT_NPMCS ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int pmc_cpu_max () ; 
 int /*<<< orphan*/  soft_allocate_pmc ; 
 int /*<<< orphan*/  soft_config_pmc ; 
 int /*<<< orphan*/  soft_describe ; 
 int /*<<< orphan*/  soft_get_config ; 
 int /*<<< orphan*/  soft_pcpu ; 
 int /*<<< orphan*/  soft_pcpu_fini ; 
 int /*<<< orphan*/  soft_pcpu_init ; 
 int /*<<< orphan*/  soft_read_pmc ; 
 int /*<<< orphan*/  soft_release_pmc ; 
 int /*<<< orphan*/  soft_start_pmc ; 
 int /*<<< orphan*/  soft_stop_pmc ; 
 int /*<<< orphan*/  soft_write_pmc ; 

void
pmc_soft_initialize(struct pmc_mdep *md)
{
	struct pmc_classdep *pcd;

	/* Add SOFT PMCs. */
	soft_pcpu = malloc(sizeof(struct soft_cpu *) * pmc_cpu_max(), M_PMC,
	    M_ZERO|M_WAITOK);

	pcd = &md->pmd_classdep[PMC_CLASS_INDEX_SOFT];

	pcd->pcd_caps	= SOFT_CAPS;
	pcd->pcd_class	= PMC_CLASS_SOFT;
	pcd->pcd_num	= SOFT_NPMCS;
	pcd->pcd_ri	= md->pmd_npmc;
	pcd->pcd_width	= 64;

	pcd->pcd_allocate_pmc = soft_allocate_pmc;
	pcd->pcd_config_pmc   = soft_config_pmc;
	pcd->pcd_describe     = soft_describe;
	pcd->pcd_get_config   = soft_get_config;
	pcd->pcd_get_msr      = NULL;
	pcd->pcd_pcpu_init    = soft_pcpu_init;
	pcd->pcd_pcpu_fini    = soft_pcpu_fini;
	pcd->pcd_read_pmc     = soft_read_pmc;
	pcd->pcd_write_pmc    = soft_write_pmc;
	pcd->pcd_release_pmc  = soft_release_pmc;
	pcd->pcd_start_pmc    = soft_start_pmc;
	pcd->pcd_stop_pmc     = soft_stop_pmc;

	md->pmd_npmc += SOFT_NPMCS;
}