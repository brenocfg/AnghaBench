#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int disabled; int /*<<< orphan*/  bp_type; int /*<<< orphan*/  bp_len; int /*<<< orphan*/  bp_addr; } ;
struct perf_event {TYPE_1__ attr; } ;
struct arch_hw_breakpoint {int /*<<< orphan*/  type; int /*<<< orphan*/  len; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  pev; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int HBP_NUM ; 
 int arch_install_hw_breakpoint (struct perf_event*) ; 
 TYPE_2__* breakinfo ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 scalar_t__ dbg_is_early ; 
 int /*<<< orphan*/  early_dr7 ; 
 int /*<<< orphan*/  encode_dr7 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_breakpoint_restore () ; 
 struct perf_event** per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_debugreg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kgdb_correct_hw_break(void)
{
	int breakno;

	for (breakno = 0; breakno < HBP_NUM; breakno++) {
		struct perf_event *bp;
		struct arch_hw_breakpoint *info;
		int val;
		int cpu = raw_smp_processor_id();
		if (!breakinfo[breakno].enabled)
			continue;
		if (dbg_is_early) {
			set_debugreg(breakinfo[breakno].addr, breakno);
			early_dr7 |= encode_dr7(breakno,
						breakinfo[breakno].len,
						breakinfo[breakno].type);
			set_debugreg(early_dr7, 7);
			continue;
		}
		bp = *per_cpu_ptr(breakinfo[breakno].pev, cpu);
		info = counter_arch_bp(bp);
		if (bp->attr.disabled != 1)
			continue;
		bp->attr.bp_addr = breakinfo[breakno].addr;
		bp->attr.bp_len = breakinfo[breakno].len;
		bp->attr.bp_type = breakinfo[breakno].type;
		info->address = breakinfo[breakno].addr;
		info->len = breakinfo[breakno].len;
		info->type = breakinfo[breakno].type;
		val = arch_install_hw_breakpoint(bp);
		if (!val)
			bp->attr.disabled = 0;
	}
	if (!dbg_is_early)
		hw_breakpoint_restore();
}