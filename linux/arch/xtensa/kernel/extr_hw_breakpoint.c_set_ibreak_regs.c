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
struct arch_hw_breakpoint {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ SREG_IBREAKA ; 
 int /*<<< orphan*/  SREG_IBREAKENABLE ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 unsigned long xtensa_get_sr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtensa_set_sr (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtensa_wsr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void set_ibreak_regs(int reg, struct perf_event *bp)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	unsigned long ibreakenable;

	xtensa_wsr(info->address, SREG_IBREAKA + reg);
	ibreakenable = xtensa_get_sr(SREG_IBREAKENABLE);
	xtensa_set_sr(ibreakenable | (1 << reg), SREG_IBREAKENABLE);
}