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
typedef  int u64 ;
struct perf_event_attr {int dummy; } ;
struct TYPE_4__ {scalar_t__ target; } ;
struct perf_event {TYPE_2__ hw; } ;
struct TYPE_3__ {int len; scalar_t__ type; scalar_t__ privilege; } ;
struct arch_hw_breakpoint {int address; TYPE_1__ ctrl; } ;

/* Variables and functions */
 scalar_t__ AARCH64_BREAKPOINT_EL1 ; 
 scalar_t__ ARM_BREAKPOINT_EXECUTE ; 
 int ARM_BREAKPOINT_LEN_1 ; 
 int ARM_BREAKPOINT_LEN_2 ; 
 int ARM_BREAKPOINT_LEN_8 ; 
 int EINVAL ; 
 int arch_build_bp_info (struct perf_event*,struct perf_event_attr const*,struct arch_hw_breakpoint*) ; 
 scalar_t__ is_compat_bp (struct perf_event*) ; 

int hw_breakpoint_arch_parse(struct perf_event *bp,
			     const struct perf_event_attr *attr,
			     struct arch_hw_breakpoint *hw)
{
	int ret;
	u64 alignment_mask, offset;

	/* Build the arch_hw_breakpoint. */
	ret = arch_build_bp_info(bp, attr, hw);
	if (ret)
		return ret;

	/*
	 * Check address alignment.
	 * We don't do any clever alignment correction for watchpoints
	 * because using 64-bit unaligned addresses is deprecated for
	 * AArch64.
	 *
	 * AArch32 tasks expect some simple alignment fixups, so emulate
	 * that here.
	 */
	if (is_compat_bp(bp)) {
		if (hw->ctrl.len == ARM_BREAKPOINT_LEN_8)
			alignment_mask = 0x7;
		else
			alignment_mask = 0x3;
		offset = hw->address & alignment_mask;
		switch (offset) {
		case 0:
			/* Aligned */
			break;
		case 1:
		case 2:
			/* Allow halfword watchpoints and breakpoints. */
			if (hw->ctrl.len == ARM_BREAKPOINT_LEN_2)
				break;

			/* Fallthrough */
		case 3:
			/* Allow single byte watchpoint. */
			if (hw->ctrl.len == ARM_BREAKPOINT_LEN_1)
				break;

			/* Fallthrough */
		default:
			return -EINVAL;
		}
	} else {
		if (hw->ctrl.type == ARM_BREAKPOINT_EXECUTE)
			alignment_mask = 0x3;
		else
			alignment_mask = 0x7;
		offset = hw->address & alignment_mask;
	}

	hw->address &= ~alignment_mask;
	hw->ctrl.len <<= offset;

	/*
	 * Disallow per-task kernel breakpoints since these would
	 * complicate the stepping code.
	 */
	if (hw->ctrl.privilege == AARCH64_BREAKPOINT_EL1 && bp->hw.target)
		return -EINVAL;

	return 0;
}