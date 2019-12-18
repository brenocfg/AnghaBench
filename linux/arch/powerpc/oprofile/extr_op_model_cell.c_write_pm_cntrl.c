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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int enable; int stop_at_max; scalar_t__ trace_mode; int trace_buf_ovflw; int freeze; int /*<<< orphan*/  count_mode; int /*<<< orphan*/  spu_addr_trace; } ;
struct TYPE_4__ {TYPE_1__ pm_cntrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBE_PM_COUNT_MODE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBE_PM_ENABLE_PERF_MON ; 
 int /*<<< orphan*/  CBE_PM_FREEZE_ALL_CTRS ; 
 int /*<<< orphan*/  CBE_PM_SPU_ADDR_TRACE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBE_PM_STOP_AT_MAX ; 
 int /*<<< orphan*/  CBE_PM_TRACE_BUF_OVFLW (int) ; 
 int /*<<< orphan*/  CBE_PM_TRACE_MODE_SET (scalar_t__) ; 
 int /*<<< orphan*/  cbe_write_pm (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_control ; 
 TYPE_2__ pm_regs ; 

__attribute__((used)) static void write_pm_cntrl(int cpu)
{
	/*
	 * Oprofile will use 32 bit counters, set bits 7:10 to 0
	 * pmregs.pm_cntrl is a global
	 */

	u32 val = 0;
	if (pm_regs.pm_cntrl.enable == 1)
		val |= CBE_PM_ENABLE_PERF_MON;

	if (pm_regs.pm_cntrl.stop_at_max == 1)
		val |= CBE_PM_STOP_AT_MAX;

	if (pm_regs.pm_cntrl.trace_mode != 0)
		val |= CBE_PM_TRACE_MODE_SET(pm_regs.pm_cntrl.trace_mode);

	if (pm_regs.pm_cntrl.trace_buf_ovflw == 1)
		val |= CBE_PM_TRACE_BUF_OVFLW(pm_regs.pm_cntrl.trace_buf_ovflw);
	if (pm_regs.pm_cntrl.freeze == 1)
		val |= CBE_PM_FREEZE_ALL_CTRS;

	val |= CBE_PM_SPU_ADDR_TRACE_SET(pm_regs.pm_cntrl.spu_addr_trace);

	/*
	 * Routine set_count_mode must be called previously to set
	 * the count mode based on the user selection of user and kernel.
	 */
	val |= CBE_PM_COUNT_MODE_SET(pm_regs.pm_cntrl.count_mode);
	cbe_write_pm(cpu, pm_control, val);
}