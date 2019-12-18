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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ exclude_kernel; scalar_t__ exclude_hv; scalar_t__ exclude_user; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int EVENT_IFM_MASK ; 
 int EVENT_IFM_SHIFT ; 
 int EVENT_IS_L1 ; 
 int EVENT_PMC_MASK ; 
 int EVENT_PMC_SHIFT ; 
 int EVENT_PSEL_MASK ; 
 int EVENT_SAMPLE_MASK ; 
 int EVENT_SAMPLE_SHIFT ; 
 int EVENT_THR_CMP_MASK ; 
 int EVENT_THR_CMP_SHIFT ; 
 int EVENT_THR_CTL_MASK ; 
 int EVENT_THR_CTL_SHIFT ; 
 int EVENT_THR_SEL_MASK ; 
 int EVENT_THR_SEL_SHIFT ; 
 int EVENT_UNIT_MASK ; 
 int EVENT_UNIT_SHIFT ; 
 int EVENT_WANTS_BHRB ; 
 unsigned long MMCR0_FC56 ; 
 unsigned long MMCR0_PMC1CE ; 
 unsigned long MMCR0_PMCjCE ; 
 unsigned long MMCR1_DC_IC_QUAL_SHIFT ; 
 int MMCR1_FAB_SHIFT ; 
 unsigned long MMCR1_PMCSEL_SHIFT (unsigned int) ; 
 unsigned long MMCR1_UNIT_SHIFT (unsigned int) ; 
 unsigned long MMCR2_FCH (unsigned int) ; 
 unsigned long MMCR2_FCP (unsigned int) ; 
 unsigned long MMCR2_FCS (unsigned int) ; 
 unsigned long MMCRA_IFM_SHIFT ; 
 unsigned long MMCRA_SAMPLE_ENABLE ; 
 unsigned long MMCRA_SAMP_ELIG_SHIFT ; 
 unsigned long MMCRA_SAMP_MODE_SHIFT ; 
 unsigned long MMCRA_THR_CTL_SHIFT ; 
 unsigned long MMCRA_THR_SEL_SHIFT ; 
 unsigned long combine_from_event (int) ; 
 unsigned long combine_shift (unsigned int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned long dc_ic_rld_quad_l1_sel (int) ; 
 scalar_t__ event_is_fab_match (int) ; 
 scalar_t__ is_event_marked (int) ; 
 int /*<<< orphan*/  mmcra_sdar_mode (int,unsigned long*) ; 
 unsigned long thresh_cmp_val (unsigned long) ; 

int isa207_compute_mmcr(u64 event[], int n_ev,
			       unsigned int hwc[], unsigned long mmcr[],
			       struct perf_event *pevents[])
{
	unsigned long mmcra, mmcr1, mmcr2, unit, combine, psel, cache, val;
	unsigned int pmc, pmc_inuse;
	int i;

	pmc_inuse = 0;

	/* First pass to count resource use */
	for (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		if (pmc)
			pmc_inuse |= 1 << pmc;
	}

	mmcra = mmcr1 = mmcr2 = 0;

	/* Second pass: assign PMCs, set all MMCR1 fields */
	for (i = 0; i < n_ev; ++i) {
		pmc     = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		unit    = (event[i] >> EVENT_UNIT_SHIFT) & EVENT_UNIT_MASK;
		combine = combine_from_event(event[i]);
		psel    =  event[i] & EVENT_PSEL_MASK;

		if (!pmc) {
			for (pmc = 1; pmc <= 4; ++pmc) {
				if (!(pmc_inuse & (1 << pmc)))
					break;
			}

			pmc_inuse |= 1 << pmc;
		}

		if (pmc <= 4) {
			mmcr1 |= unit << MMCR1_UNIT_SHIFT(pmc);
			mmcr1 |= combine << combine_shift(pmc);
			mmcr1 |= psel << MMCR1_PMCSEL_SHIFT(pmc);
		}

		/* In continuous sampling mode, update SDAR on TLB miss */
		mmcra_sdar_mode(event[i], &mmcra);

		if (cpu_has_feature(CPU_FTR_ARCH_300)) {
			cache = dc_ic_rld_quad_l1_sel(event[i]);
			mmcr1 |= (cache) << MMCR1_DC_IC_QUAL_SHIFT;
		} else {
			if (event[i] & EVENT_IS_L1) {
				cache = dc_ic_rld_quad_l1_sel(event[i]);
				mmcr1 |= (cache) << MMCR1_DC_IC_QUAL_SHIFT;
			}
		}

		if (is_event_marked(event[i])) {
			mmcra |= MMCRA_SAMPLE_ENABLE;

			val = (event[i] >> EVENT_SAMPLE_SHIFT) & EVENT_SAMPLE_MASK;
			if (val) {
				mmcra |= (val &  3) << MMCRA_SAMP_MODE_SHIFT;
				mmcra |= (val >> 2) << MMCRA_SAMP_ELIG_SHIFT;
			}
		}

		/*
		 * PM_MRK_FAB_RSP_MATCH and PM_MRK_FAB_RSP_MATCH_CYC,
		 * the threshold bits are used for the match value.
		 */
		if (!cpu_has_feature(CPU_FTR_ARCH_300) && event_is_fab_match(event[i])) {
			mmcr1 |= ((event[i] >> EVENT_THR_CTL_SHIFT) &
				  EVENT_THR_CTL_MASK) << MMCR1_FAB_SHIFT;
		} else {
			val = (event[i] >> EVENT_THR_CTL_SHIFT) & EVENT_THR_CTL_MASK;
			mmcra |= val << MMCRA_THR_CTL_SHIFT;
			val = (event[i] >> EVENT_THR_SEL_SHIFT) & EVENT_THR_SEL_MASK;
			mmcra |= val << MMCRA_THR_SEL_SHIFT;
			val = (event[i] >> EVENT_THR_CMP_SHIFT) & EVENT_THR_CMP_MASK;
			mmcra |= thresh_cmp_val(val);
		}

		if (event[i] & EVENT_WANTS_BHRB) {
			val = (event[i] >> EVENT_IFM_SHIFT) & EVENT_IFM_MASK;
			mmcra |= val << MMCRA_IFM_SHIFT;
		}

		if (pevents[i]->attr.exclude_user)
			mmcr2 |= MMCR2_FCP(pmc);

		if (pevents[i]->attr.exclude_hv)
			mmcr2 |= MMCR2_FCH(pmc);

		if (pevents[i]->attr.exclude_kernel) {
			if (cpu_has_feature(CPU_FTR_HVMODE))
				mmcr2 |= MMCR2_FCH(pmc);
			else
				mmcr2 |= MMCR2_FCS(pmc);
		}

		hwc[i] = pmc - 1;
	}

	/* Return MMCRx values */
	mmcr[0] = 0;

	/* pmc_inuse is 1-based */
	if (pmc_inuse & 2)
		mmcr[0] = MMCR0_PMC1CE;

	if (pmc_inuse & 0x7c)
		mmcr[0] |= MMCR0_PMCjCE;

	/* If we're not using PMC 5 or 6, freeze them */
	if (!(pmc_inuse & 0x60))
		mmcr[0] |= MMCR0_FC56;

	mmcr[1] = mmcr1;
	mmcr[2] = mmcra;
	mmcr[3] = mmcr2;

	return 0;
}