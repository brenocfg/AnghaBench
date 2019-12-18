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
typedef  int vm_fault_t ;
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct TYPE_3__ {unsigned long gmap_addr; int gmap_write_flag; int gmap_int_code; int gmap_pfault; } ;
struct task_struct {TYPE_1__ thread; int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; struct mm_struct* mm; } ;
struct pt_regs {unsigned long int_parm_long; int int_code; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct gmap {scalar_t__ pfault_enabled; } ;
typedef  enum fault_type { ____Placeholder_fault_type } fault_type ;
struct TYPE_4__ {scalar_t__ gmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PGSTE ; 
 unsigned long EFAULT ; 
 unsigned long ENOMEM ; 
 unsigned int FAULT_FLAG_ALLOW_RETRY ; 
 unsigned int FAULT_FLAG_KILLABLE ; 
 unsigned int FAULT_FLAG_RETRY_NOWAIT ; 
 unsigned int FAULT_FLAG_TRIED ; 
 unsigned int FAULT_FLAG_USER ; 
 unsigned int FAULT_FLAG_WRITE ; 
#define  GMAP_FAULT 131 
 unsigned long HPAGE_MASK ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  KERNEL_FAULT 130 
 int /*<<< orphan*/  PERF_COUNT_SW_PAGE_FAULTS ; 
 int /*<<< orphan*/  PERF_COUNT_SW_PAGE_FAULTS_MAJ ; 
 int /*<<< orphan*/  PERF_COUNT_SW_PAGE_FAULTS_MIN ; 
 int /*<<< orphan*/  PIF_PER_TRAP ; 
 TYPE_2__ S390_lowcore ; 
#define  USER_FAULT 129 
#define  VDSO_FAULT 128 
 int VM_FAULT_BADACCESS ; 
 int VM_FAULT_BADCONTEXT ; 
 int VM_FAULT_BADMAP ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_PFAULT ; 
 int VM_FAULT_RETRY ; 
 int VM_FAULT_SIGNAL ; 
 int VM_GROWSDOWN ; 
 int VM_WRITE ; 
 unsigned long __FAIL_ADDR_MASK ; 
 unsigned long __gmap_link (struct gmap*,unsigned long,unsigned long) ; 
 unsigned long __gmap_translate (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  clear_pt_regs_flag (struct pt_regs*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_stack (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ fatal_signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  faulthandler_disabled () ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int get_fault_type (struct pt_regs*) ; 
 int handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 scalar_t__ kprobe_page_fault (struct pt_regs*,int) ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,unsigned long) ; 
 unsigned long store_indication ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static inline vm_fault_t do_exception(struct pt_regs *regs, int access)
{
	struct gmap *gmap;
	struct task_struct *tsk;
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	enum fault_type type;
	unsigned long trans_exc_code;
	unsigned long address;
	unsigned int flags;
	vm_fault_t fault;

	tsk = current;
	/*
	 * The instruction that caused the program check has
	 * been nullified. Don't signal single step via SIGTRAP.
	 */
	clear_pt_regs_flag(regs, PIF_PER_TRAP);

	if (kprobe_page_fault(regs, 14))
		return 0;

	mm = tsk->mm;
	trans_exc_code = regs->int_parm_long;

	/*
	 * Verify that the fault happened in user space, that
	 * we are not in an interrupt and that there is a 
	 * user context.
	 */
	fault = VM_FAULT_BADCONTEXT;
	type = get_fault_type(regs);
	switch (type) {
	case KERNEL_FAULT:
		goto out;
	case VDSO_FAULT:
		fault = VM_FAULT_BADMAP;
		goto out;
	case USER_FAULT:
	case GMAP_FAULT:
		if (faulthandler_disabled() || !mm)
			goto out;
		break;
	}

	address = trans_exc_code & __FAIL_ADDR_MASK;
	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
	flags = FAULT_FLAG_ALLOW_RETRY | FAULT_FLAG_KILLABLE;
	if (user_mode(regs))
		flags |= FAULT_FLAG_USER;
	if (access == VM_WRITE || (trans_exc_code & store_indication) == 0x400)
		flags |= FAULT_FLAG_WRITE;
	down_read(&mm->mmap_sem);

	gmap = NULL;
	if (IS_ENABLED(CONFIG_PGSTE) && type == GMAP_FAULT) {
		gmap = (struct gmap *) S390_lowcore.gmap;
		current->thread.gmap_addr = address;
		current->thread.gmap_write_flag = !!(flags & FAULT_FLAG_WRITE);
		current->thread.gmap_int_code = regs->int_code & 0xffff;
		address = __gmap_translate(gmap, address);
		if (address == -EFAULT) {
			fault = VM_FAULT_BADMAP;
			goto out_up;
		}
		if (gmap->pfault_enabled)
			flags |= FAULT_FLAG_RETRY_NOWAIT;
	}

retry:
	fault = VM_FAULT_BADMAP;
	vma = find_vma(mm, address);
	if (!vma)
		goto out_up;

	if (unlikely(vma->vm_start > address)) {
		if (!(vma->vm_flags & VM_GROWSDOWN))
			goto out_up;
		if (expand_stack(vma, address))
			goto out_up;
	}

	/*
	 * Ok, we have a good vm_area for this memory access, so
	 * we can handle it..
	 */
	fault = VM_FAULT_BADACCESS;
	if (unlikely(!(vma->vm_flags & access)))
		goto out_up;

	if (is_vm_hugetlb_page(vma))
		address &= HPAGE_MASK;
	/*
	 * If for any reason at all we couldn't handle the fault,
	 * make sure we exit gracefully rather than endlessly redo
	 * the fault.
	 */
	fault = handle_mm_fault(vma, address, flags);
	/* No reason to continue if interrupted by SIGKILL. */
	if ((fault & VM_FAULT_RETRY) && fatal_signal_pending(current)) {
		fault = VM_FAULT_SIGNAL;
		if (flags & FAULT_FLAG_RETRY_NOWAIT)
			goto out_up;
		goto out;
	}
	if (unlikely(fault & VM_FAULT_ERROR))
		goto out_up;

	/*
	 * Major/minor page fault accounting is only done on the
	 * initial attempt. If we go through a retry, it is extremely
	 * likely that the page will be found in page cache at that point.
	 */
	if (flags & FAULT_FLAG_ALLOW_RETRY) {
		if (fault & VM_FAULT_MAJOR) {
			tsk->maj_flt++;
			perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1,
				      regs, address);
		} else {
			tsk->min_flt++;
			perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1,
				      regs, address);
		}
		if (fault & VM_FAULT_RETRY) {
			if (IS_ENABLED(CONFIG_PGSTE) && gmap &&
			    (flags & FAULT_FLAG_RETRY_NOWAIT)) {
				/* FAULT_FLAG_RETRY_NOWAIT has been set,
				 * mmap_sem has not been released */
				current->thread.gmap_pfault = 1;
				fault = VM_FAULT_PFAULT;
				goto out_up;
			}
			/* Clear FAULT_FLAG_ALLOW_RETRY to avoid any risk
			 * of starvation. */
			flags &= ~(FAULT_FLAG_ALLOW_RETRY |
				   FAULT_FLAG_RETRY_NOWAIT);
			flags |= FAULT_FLAG_TRIED;
			down_read(&mm->mmap_sem);
			goto retry;
		}
	}
	if (IS_ENABLED(CONFIG_PGSTE) && gmap) {
		address =  __gmap_link(gmap, current->thread.gmap_addr,
				       address);
		if (address == -EFAULT) {
			fault = VM_FAULT_BADMAP;
			goto out_up;
		}
		if (address == -ENOMEM) {
			fault = VM_FAULT_OOM;
			goto out_up;
		}
	}
	fault = 0;
out_up:
	up_read(&mm->mmap_sem);
out:
	return fault;
}