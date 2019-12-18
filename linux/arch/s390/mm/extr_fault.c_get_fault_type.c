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
struct pt_regs {int int_parm_long; } ;
typedef  enum fault_type { ____Placeholder_fault_type } fault_type ;
struct TYPE_3__ {int mm_segment; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PGSTE ; 
 int GMAP_FAULT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int KERNEL_FAULT ; 
 int /*<<< orphan*/  PIF_GUEST_FAULT ; 
 int USER_DS ; 
 int USER_DS_SACF ; 
 int USER_FAULT ; 
 int VDSO_FAULT ; 
 TYPE_2__* current ; 
 scalar_t__ likely (int) ; 
 scalar_t__ test_pt_regs_flag (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fault_type get_fault_type(struct pt_regs *regs)
{
	unsigned long trans_exc_code;

	trans_exc_code = regs->int_parm_long & 3;
	if (likely(trans_exc_code == 0)) {
		/* primary space exception */
		if (IS_ENABLED(CONFIG_PGSTE) &&
		    test_pt_regs_flag(regs, PIF_GUEST_FAULT))
			return GMAP_FAULT;
		if (current->thread.mm_segment == USER_DS)
			return USER_FAULT;
		return KERNEL_FAULT;
	}
	if (trans_exc_code == 2) {
		/* secondary space exception */
		if (current->thread.mm_segment & 1) {
			if (current->thread.mm_segment == USER_DS_SACF)
				return USER_FAULT;
			return KERNEL_FAULT;
		}
		return VDSO_FAULT;
	}
	if (trans_exc_code == 1) {
		/* access register mode, not used in the kernel */
		return USER_FAULT;
	}
	/* home space exception -> access via kernel ASCE */
	return KERNEL_FAULT;
}