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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned long) ; 
 unsigned long X86_PF_PK ; 
 unsigned long X86_PF_PROT ; 
 unsigned long X86_PF_RSVD ; 
 unsigned long X86_PF_USER ; 
 int /*<<< orphan*/  X86_TRAP_PF ; 
 int /*<<< orphan*/  bad_area_nosemaphore (struct pt_regs*,unsigned long,unsigned long) ; 
 scalar_t__ kprobe_page_fault (struct pt_regs*,int /*<<< orphan*/ ) ; 
 scalar_t__ spurious_kernel_fault (unsigned long,unsigned long) ; 
 scalar_t__ vmalloc_fault (unsigned long) ; 

__attribute__((used)) static void
do_kern_addr_fault(struct pt_regs *regs, unsigned long hw_error_code,
		   unsigned long address)
{
	/*
	 * Protection keys exceptions only happen on user pages.  We
	 * have no user pages in the kernel portion of the address
	 * space, so do not expect them here.
	 */
	WARN_ON_ONCE(hw_error_code & X86_PF_PK);

	/*
	 * We can fault-in kernel-space virtual memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks for this case. We may
	 * be in an interrupt or a critical region, and should
	 * only copy the information from the master page table,
	 * nothing more.
	 *
	 * Before doing this on-demand faulting, ensure that the
	 * fault is not any of the following:
	 * 1. A fault on a PTE with a reserved bit set.
	 * 2. A fault caused by a user-mode access.  (Do not demand-
	 *    fault kernel memory due to user-mode accesses).
	 * 3. A fault caused by a page-level protection violation.
	 *    (A demand fault would be on a non-present page which
	 *     would have X86_PF_PROT==0).
	 */
	if (!(hw_error_code & (X86_PF_RSVD | X86_PF_USER | X86_PF_PROT))) {
		if (vmalloc_fault(address) >= 0)
			return;
	}

	/* Was the fault spurious, caused by lazy TLB invalidation? */
	if (spurious_kernel_fault(hw_error_code, address))
		return;

	/* kprobes don't want to hook the spurious faults: */
	if (kprobe_page_fault(regs, X86_TRAP_PF))
		return;

	/*
	 * Note, despite being a "bad area", there are quite a few
	 * acceptable reasons to get here, such as erratum fixups
	 * and handling kernel code that can fault, like get_user().
	 *
	 * Don't take the mm semaphore here. If we fixup a prefetch
	 * fault we could otherwise deadlock:
	 */
	bad_area_nosemaphore(regs, hw_error_code, address);
}