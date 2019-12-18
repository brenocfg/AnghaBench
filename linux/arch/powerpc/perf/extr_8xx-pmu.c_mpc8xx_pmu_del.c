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
struct perf_event {int dummy; } ;

/* Variables and functions */
#define  PERF_8xx_ID_CPU_CYCLES 131 
#define  PERF_8xx_ID_DTLB_LOAD_MISS 130 
#define  PERF_8xx_ID_HW_INSTRUCTIONS 129 
#define  PERF_8xx_ID_ITLB_LOAD_MISS 128 
 unsigned int PPC_INST_MFSPR ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  SPRN_ICTRL ; 
 int /*<<< orphan*/  SPRN_SPRG_SCRATCH0 ; 
 unsigned int __PPC_RS (int /*<<< orphan*/ ) ; 
 unsigned int __PPC_SPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtlb_miss_ref ; 
 int event_type (struct perf_event*) ; 
 int /*<<< orphan*/  insn_ctr_ref ; 
 int /*<<< orphan*/  itlb_miss_ref ; 
 int /*<<< orphan*/  mpc8xx_pmu_read (struct perf_event*) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patch__dtlbmiss_exit_1 ; 
 int /*<<< orphan*/  patch__dtlbmiss_exit_2 ; 
 int /*<<< orphan*/  patch__dtlbmiss_exit_3 ; 
 int /*<<< orphan*/  patch__itlbmiss_exit_1 ; 
 int /*<<< orphan*/  patch__itlbmiss_exit_2 ; 
 int /*<<< orphan*/  patch_instruction_site (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mpc8xx_pmu_del(struct perf_event *event, int flags)
{
	/* mfspr r10, SPRN_SPRG_SCRATCH0 */
	unsigned int insn = PPC_INST_MFSPR | __PPC_RS(R10) |
			    __PPC_SPR(SPRN_SPRG_SCRATCH0);

	mpc8xx_pmu_read(event);

	/* If it was the last user, stop counting to avoid useles overhead */
	switch (event_type(event)) {
	case PERF_8xx_ID_CPU_CYCLES:
		break;
	case PERF_8xx_ID_HW_INSTRUCTIONS:
		if (atomic_dec_return(&insn_ctr_ref) == 0)
			mtspr(SPRN_ICTRL, 7);
		break;
	case PERF_8xx_ID_ITLB_LOAD_MISS:
		if (atomic_dec_return(&itlb_miss_ref) == 0) {
			patch_instruction_site(&patch__itlbmiss_exit_1, insn);
#ifndef CONFIG_PIN_TLB_TEXT
			patch_instruction_site(&patch__itlbmiss_exit_2, insn);
#endif
		}
		break;
	case PERF_8xx_ID_DTLB_LOAD_MISS:
		if (atomic_dec_return(&dtlb_miss_ref) == 0) {
			patch_instruction_site(&patch__dtlbmiss_exit_1, insn);
			patch_instruction_site(&patch__dtlbmiss_exit_2, insn);
			patch_instruction_site(&patch__dtlbmiss_exit_3, insn);
		}
		break;
	}
}