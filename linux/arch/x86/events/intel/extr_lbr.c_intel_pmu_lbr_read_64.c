#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u16 ;
struct TYPE_9__ {int nr; } ;
struct cpu_hw_events {TYPE_4__ lbr_stack; TYPE_3__* lbr_entries; TYPE_2__* lbr_sel; } ;
typedef  int s64 ;
struct TYPE_6__ {int lbr_format; } ;
struct TYPE_10__ {int lbr_nr; scalar_t__ lbr_double_abort; TYPE_1__ intel_cap; } ;
struct TYPE_8__ {int from; int to; int mispred; int predicted; int in_tx; int abort; int cycles; scalar_t__ reserved; scalar_t__ type; } ;
struct TYPE_7__ {int config; } ;

/* Variables and functions */
 int LBR_CALL_STACK ; 
 int LBR_EIP_FLAGS ; 
 int LBR_FORMAT_INFO ; 
 int LBR_FORMAT_TIME ; 
 int LBR_FROM_FLAG_ABORT ; 
 int LBR_FROM_FLAG_IN_TX ; 
 int LBR_FROM_FLAG_MISPRED ; 
 int LBR_INFO_ABORT ; 
 int LBR_INFO_CYCLES ; 
 int LBR_INFO_IN_TX ; 
 int LBR_INFO_MISPRED ; 
 int LBR_NO_INFO ; 
 int LBR_TSX ; 
 scalar_t__ MSR_LBR_INFO_0 ; 
 int intel_pmu_lbr_tos () ; 
 int* lbr_desc ; 
 int rdlbr_from (unsigned long) ; 
 int rdlbr_to (unsigned long) ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int) ; 
 TYPE_5__ x86_pmu ; 

__attribute__((used)) static void intel_pmu_lbr_read_64(struct cpu_hw_events *cpuc)
{
	bool need_info = false, call_stack = false;
	unsigned long mask = x86_pmu.lbr_nr - 1;
	int lbr_format = x86_pmu.intel_cap.lbr_format;
	u64 tos = intel_pmu_lbr_tos();
	int i;
	int out = 0;
	int num = x86_pmu.lbr_nr;

	if (cpuc->lbr_sel) {
		need_info = !(cpuc->lbr_sel->config & LBR_NO_INFO);
		if (cpuc->lbr_sel->config & LBR_CALL_STACK)
			call_stack = true;
	}

	for (i = 0; i < num; i++) {
		unsigned long lbr_idx = (tos - i) & mask;
		u64 from, to, mis = 0, pred = 0, in_tx = 0, abort = 0;
		int skip = 0;
		u16 cycles = 0;
		int lbr_flags = lbr_desc[lbr_format];

		from = rdlbr_from(lbr_idx);
		to   = rdlbr_to(lbr_idx);

		/*
		 * Read LBR call stack entries
		 * until invalid entry (0s) is detected.
		 */
		if (call_stack && !from)
			break;

		if (lbr_format == LBR_FORMAT_INFO && need_info) {
			u64 info;

			rdmsrl(MSR_LBR_INFO_0 + lbr_idx, info);
			mis = !!(info & LBR_INFO_MISPRED);
			pred = !mis;
			in_tx = !!(info & LBR_INFO_IN_TX);
			abort = !!(info & LBR_INFO_ABORT);
			cycles = (info & LBR_INFO_CYCLES);
		}

		if (lbr_format == LBR_FORMAT_TIME) {
			mis = !!(from & LBR_FROM_FLAG_MISPRED);
			pred = !mis;
			skip = 1;
			cycles = ((to >> 48) & LBR_INFO_CYCLES);

			to = (u64)((((s64)to) << 16) >> 16);
		}

		if (lbr_flags & LBR_EIP_FLAGS) {
			mis = !!(from & LBR_FROM_FLAG_MISPRED);
			pred = !mis;
			skip = 1;
		}
		if (lbr_flags & LBR_TSX) {
			in_tx = !!(from & LBR_FROM_FLAG_IN_TX);
			abort = !!(from & LBR_FROM_FLAG_ABORT);
			skip = 3;
		}
		from = (u64)((((s64)from) << skip) >> skip);

		/*
		 * Some CPUs report duplicated abort records,
		 * with the second entry not having an abort bit set.
		 * Skip them here. This loop runs backwards,
		 * so we need to undo the previous record.
		 * If the abort just happened outside the window
		 * the extra entry cannot be removed.
		 */
		if (abort && x86_pmu.lbr_double_abort && out > 0)
			out--;

		cpuc->lbr_entries[out].from	 = from;
		cpuc->lbr_entries[out].to	 = to;
		cpuc->lbr_entries[out].mispred	 = mis;
		cpuc->lbr_entries[out].predicted = pred;
		cpuc->lbr_entries[out].in_tx	 = in_tx;
		cpuc->lbr_entries[out].abort	 = abort;
		cpuc->lbr_entries[out].cycles	 = cycles;
		cpuc->lbr_entries[out].type	 = 0;
		cpuc->lbr_entries[out].reserved	 = 0;
		out++;
	}
	cpuc->lbr_stack.nr = out;
}