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
typedef  enum hw_breakpoint_ops { ____Placeholder_hw_breakpoint_ops } hw_breakpoint_ops ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
#define  HW_BREAKPOINT_INSTALL 130 
#define  HW_BREAKPOINT_RESTORE 129 
#define  HW_BREAKPOINT_UNINSTALL 128 
 int /*<<< orphan*/  pr_warn_once (char*,int) ; 

__attribute__((used)) static int hw_breakpoint_slot_setup(struct perf_event **slots, int max_slots,
				    struct perf_event *bp,
				    enum hw_breakpoint_ops ops)
{
	int i;
	struct perf_event **slot;

	for (i = 0; i < max_slots; ++i) {
		slot = &slots[i];
		switch (ops) {
		case HW_BREAKPOINT_INSTALL:
			if (!*slot) {
				*slot = bp;
				return i;
			}
			break;
		case HW_BREAKPOINT_UNINSTALL:
			if (*slot == bp) {
				*slot = NULL;
				return i;
			}
			break;
		case HW_BREAKPOINT_RESTORE:
			if (*slot == bp)
				return i;
			break;
		default:
			pr_warn_once("Unhandled hw breakpoint ops %d\n", ops);
			return -EINVAL;
		}
	}
	return -ENOSPC;
}