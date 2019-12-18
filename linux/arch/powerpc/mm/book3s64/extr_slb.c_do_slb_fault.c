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
struct pt_regs {int msr; } ;
struct mm_struct {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;
struct TYPE_3__ {int in_kernel_slb_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 long EFAULT ; 
 long EINVAL ; 
 unsigned long LINEAR_MAP_REGION_ID ; 
 int MSR_EE ; 
 int MSR_RI ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_thread_info () ; 
 unsigned long get_region_id (unsigned long) ; 
 TYPE_1__* local_paca ; 
 int mfmsr () ; 
 int /*<<< orphan*/  preload_add (int /*<<< orphan*/ ,unsigned long) ; 
 long slb_allocate_kernel (unsigned long,unsigned long) ; 
 long slb_allocate_user (struct mm_struct*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

long do_slb_fault(struct pt_regs *regs, unsigned long ea)
{
	unsigned long id = get_region_id(ea);

	/* IRQs are not reconciled here, so can't check irqs_disabled */
	VM_WARN_ON(mfmsr() & MSR_EE);

	if (unlikely(!(regs->msr & MSR_RI)))
		return -EINVAL;

	/*
	 * SLB kernel faults must be very careful not to touch anything
	 * that is not bolted. E.g., PACA and global variables are okay,
	 * mm->context stuff is not.
	 *
	 * SLB user faults can access all of kernel memory, but must be
	 * careful not to touch things like IRQ state because it is not
	 * "reconciled" here. The difficulty is that we must use
	 * fast_exception_return to return from kernel SLB faults without
	 * looking at possible non-bolted memory. We could test user vs
	 * kernel faults in the interrupt handler asm and do a full fault,
	 * reconcile, ret_from_except for user faults which would make them
	 * first class kernel code. But for performance it's probably nicer
	 * if they go via fast_exception_return too.
	 */
	if (id >= LINEAR_MAP_REGION_ID) {
		long err;
#ifdef CONFIG_DEBUG_VM
		/* Catch recursive kernel SLB faults. */
		BUG_ON(local_paca->in_kernel_slb_handler);
		local_paca->in_kernel_slb_handler = 1;
#endif
		err = slb_allocate_kernel(ea, id);
#ifdef CONFIG_DEBUG_VM
		local_paca->in_kernel_slb_handler = 0;
#endif
		return err;
	} else {
		struct mm_struct *mm = current->mm;
		long err;

		if (unlikely(!mm))
			return -EFAULT;

		err = slb_allocate_user(mm, ea);
		if (!err)
			preload_add(current_thread_info(), ea);

		return err;
	}
}