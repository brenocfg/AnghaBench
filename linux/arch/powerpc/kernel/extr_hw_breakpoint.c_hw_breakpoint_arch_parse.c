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
struct perf_event_attr {int bp_type; int bp_addr; int bp_len; int /*<<< orphan*/  exclude_hv; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  exclude_user; } ;
struct perf_event {int dummy; } ;
struct arch_hw_breakpoint {int address; int len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int HW_BREAKPOINT_ALIGN ; 
 int HW_BREAKPOINT_R ; 
 int HW_BREAKPOINT_W ; 
 int /*<<< orphan*/  HW_BRK_TYPE_HYP ; 
 int /*<<< orphan*/  HW_BRK_TYPE_KERNEL ; 
 int /*<<< orphan*/  HW_BRK_TYPE_READ ; 
 int /*<<< orphan*/  HW_BRK_TYPE_TRANSLATE ; 
 int /*<<< orphan*/  HW_BRK_TYPE_USER ; 
 int /*<<< orphan*/  HW_BRK_TYPE_WRITE ; 
 scalar_t__ dawr_enabled () ; 
 int /*<<< orphan*/  ppc_breakpoint_available () ; 

int hw_breakpoint_arch_parse(struct perf_event *bp,
			     const struct perf_event_attr *attr,
			     struct arch_hw_breakpoint *hw)
{
	int ret = -EINVAL, length_max;

	if (!bp)
		return ret;

	hw->type = HW_BRK_TYPE_TRANSLATE;
	if (attr->bp_type & HW_BREAKPOINT_R)
		hw->type |= HW_BRK_TYPE_READ;
	if (attr->bp_type & HW_BREAKPOINT_W)
		hw->type |= HW_BRK_TYPE_WRITE;
	if (hw->type == HW_BRK_TYPE_TRANSLATE)
		/* must set alteast read or write */
		return ret;
	if (!attr->exclude_user)
		hw->type |= HW_BRK_TYPE_USER;
	if (!attr->exclude_kernel)
		hw->type |= HW_BRK_TYPE_KERNEL;
	if (!attr->exclude_hv)
		hw->type |= HW_BRK_TYPE_HYP;
	hw->address = attr->bp_addr;
	hw->len = attr->bp_len;

	/*
	 * Since breakpoint length can be a maximum of HW_BREAKPOINT_LEN(8)
	 * and breakpoint addresses are aligned to nearest double-word
	 * HW_BREAKPOINT_ALIGN by rounding off to the lower address, the
	 * 'symbolsize' should satisfy the check below.
	 */
	if (!ppc_breakpoint_available())
		return -ENODEV;
	length_max = 8; /* DABR */
	if (dawr_enabled()) {
		length_max = 512 ; /* 64 doublewords */
		/* DAWR region can't cross 512 boundary */
		if ((attr->bp_addr >> 9) !=
		    ((attr->bp_addr + attr->bp_len - 1) >> 9))
			return -EINVAL;
	}
	if (hw->len >
	    (length_max - (hw->address & HW_BREAKPOINT_ALIGN)))
		return -EINVAL;
	return 0;
}