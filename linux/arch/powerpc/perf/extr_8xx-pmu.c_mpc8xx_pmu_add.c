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
struct TYPE_2__ {int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
#define  PERF_8xx_ID_CPU_CYCLES 131 
#define  PERF_8xx_ID_DTLB_LOAD_MISS 130 
#define  PERF_8xx_ID_HW_INSTRUCTIONS 129 
#define  PERF_8xx_ID_ITLB_LOAD_MISS 128 
 int /*<<< orphan*/  SPRN_ICTRL ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtlb_miss_counter ; 
 int /*<<< orphan*/  dtlb_miss_ref ; 
 int event_type (struct perf_event*) ; 
 int /*<<< orphan*/  get_insn_ctr () ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  insn_ctr_ref ; 
 int /*<<< orphan*/  itlb_miss_counter ; 
 int /*<<< orphan*/  itlb_miss_ref ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patch__dtlbmiss_exit_1 ; 
 int /*<<< orphan*/  patch__dtlbmiss_exit_2 ; 
 int /*<<< orphan*/  patch__dtlbmiss_exit_3 ; 
 int /*<<< orphan*/  patch__dtlbmiss_perf ; 
 int /*<<< orphan*/  patch__itlbmiss_exit_1 ; 
 int /*<<< orphan*/  patch__itlbmiss_exit_2 ; 
 int /*<<< orphan*/  patch__itlbmiss_perf ; 
 int /*<<< orphan*/  patch_branch_site (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long patch_site_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc8xx_pmu_add(struct perf_event *event, int flags)
{
	int type = event_type(event);
	s64 val = 0;

	if (type < 0)
		return type;

	switch (type) {
	case PERF_8xx_ID_CPU_CYCLES:
		val = get_tb();
		break;
	case PERF_8xx_ID_HW_INSTRUCTIONS:
		if (atomic_inc_return(&insn_ctr_ref) == 1)
			mtspr(SPRN_ICTRL, 0xc0080007);
		val = get_insn_ctr();
		break;
	case PERF_8xx_ID_ITLB_LOAD_MISS:
		if (atomic_inc_return(&itlb_miss_ref) == 1) {
			unsigned long target = patch_site_addr(&patch__itlbmiss_perf);

			patch_branch_site(&patch__itlbmiss_exit_1, target, 0);
#ifndef CONFIG_PIN_TLB_TEXT
			patch_branch_site(&patch__itlbmiss_exit_2, target, 0);
#endif
		}
		val = itlb_miss_counter;
		break;
	case PERF_8xx_ID_DTLB_LOAD_MISS:
		if (atomic_inc_return(&dtlb_miss_ref) == 1) {
			unsigned long target = patch_site_addr(&patch__dtlbmiss_perf);

			patch_branch_site(&patch__dtlbmiss_exit_1, target, 0);
			patch_branch_site(&patch__dtlbmiss_exit_2, target, 0);
			patch_branch_site(&patch__dtlbmiss_exit_3, target, 0);
		}
		val = dtlb_miss_counter;
		break;
	}
	local64_set(&event->hw.prev_count, val);
	return 0;
}