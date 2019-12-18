#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_fault_t ;
struct vm_area_struct {int vm_flags; unsigned long vm_start; } ;
struct pt_regs {int /*<<< orphan*/  pc; int /*<<< orphan*/  sr; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/ * pgd; } ;
struct TYPE_4__ {unsigned long faddr; int /*<<< orphan*/  code; void* signo; } ;
struct TYPE_5__ {TYPE_1__ thread; int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUS_ADRERR ; 
 unsigned int FAULT_FLAG_ALLOW_RETRY ; 
 unsigned int FAULT_FLAG_KILLABLE ; 
 unsigned int FAULT_FLAG_TRIED ; 
 unsigned int FAULT_FLAG_USER ; 
 unsigned int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  SEGV_ACCERR ; 
 int /*<<< orphan*/  SEGV_MAPERR ; 
 void* SIGBUS ; 
 void* SIGSEGV ; 
 int VM_EXEC ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_RETRY ; 
 int VM_FAULT_SIGBUS ; 
 int VM_FAULT_SIGSEGV ; 
 int VM_GROWSDOWN ; 
 int VM_IO ; 
 int VM_READ ; 
 int VM_WRITE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_stack (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ fatal_signal_pending (TYPE_2__*) ; 
 scalar_t__ faulthandler_disabled () ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  pagefault_out_of_memory () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 unsigned long rdusp () ; 
 int send_fault_sig (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int do_page_fault(struct pt_regs *regs, unsigned long address,
			      unsigned long error_code)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct * vma;
	vm_fault_t fault;
	unsigned int flags = FAULT_FLAG_ALLOW_RETRY | FAULT_FLAG_KILLABLE;

	pr_debug("do page fault:\nregs->sr=%#x, regs->pc=%#lx, address=%#lx, %ld, %p\n",
		regs->sr, regs->pc, address, error_code, mm ? mm->pgd : NULL);

	/*
	 * If we're in an interrupt or have no user
	 * context, we must not take the fault..
	 */
	if (faulthandler_disabled() || !mm)
		goto no_context;

	if (user_mode(regs))
		flags |= FAULT_FLAG_USER;
retry:
	down_read(&mm->mmap_sem);

	vma = find_vma(mm, address);
	if (!vma)
		goto map_err;
	if (vma->vm_flags & VM_IO)
		goto acc_err;
	if (vma->vm_start <= address)
		goto good_area;
	if (!(vma->vm_flags & VM_GROWSDOWN))
		goto map_err;
	if (user_mode(regs)) {
		/* Accessing the stack below usp is always a bug.  The
		   "+ 256" is there due to some instructions doing
		   pre-decrement on the stack and that doesn't show up
		   until later.  */
		if (address + 256 < rdusp())
			goto map_err;
	}
	if (expand_stack(vma, address))
		goto map_err;

/*
 * Ok, we have a good vm_area for this memory access, so
 * we can handle it..
 */
good_area:
	pr_debug("do_page_fault: good_area\n");
	switch (error_code & 3) {
		default:	/* 3: write, present */
			/* fall through */
		case 2:		/* write, not present */
			if (!(vma->vm_flags & VM_WRITE))
				goto acc_err;
			flags |= FAULT_FLAG_WRITE;
			break;
		case 1:		/* read, present */
			goto acc_err;
		case 0:		/* read, not present */
			if (!(vma->vm_flags & (VM_READ | VM_EXEC | VM_WRITE)))
				goto acc_err;
	}

	/*
	 * If for any reason at all we couldn't handle the fault,
	 * make sure we exit gracefully rather than endlessly redo
	 * the fault.
	 */

	fault = handle_mm_fault(vma, address, flags);
	pr_debug("handle_mm_fault returns %x\n", fault);

	if ((fault & VM_FAULT_RETRY) && fatal_signal_pending(current))
		return 0;

	if (unlikely(fault & VM_FAULT_ERROR)) {
		if (fault & VM_FAULT_OOM)
			goto out_of_memory;
		else if (fault & VM_FAULT_SIGSEGV)
			goto map_err;
		else if (fault & VM_FAULT_SIGBUS)
			goto bus_err;
		BUG();
	}

	/*
	 * Major/minor page fault accounting is only done on the
	 * initial attempt. If we go through a retry, it is extremely
	 * likely that the page will be found in page cache at that point.
	 */
	if (flags & FAULT_FLAG_ALLOW_RETRY) {
		if (fault & VM_FAULT_MAJOR)
			current->maj_flt++;
		else
			current->min_flt++;
		if (fault & VM_FAULT_RETRY) {
			/* Clear FAULT_FLAG_ALLOW_RETRY to avoid any risk
			 * of starvation. */
			flags &= ~FAULT_FLAG_ALLOW_RETRY;
			flags |= FAULT_FLAG_TRIED;

			/*
			 * No need to up_read(&mm->mmap_sem) as we would
			 * have already released it in __lock_page_or_retry
			 * in mm/filemap.c.
			 */

			goto retry;
		}
	}

	up_read(&mm->mmap_sem);
	return 0;

/*
 * We ran out of memory, or some other thing happened to us that made
 * us unable to handle the page fault gracefully.
 */
out_of_memory:
	up_read(&mm->mmap_sem);
	if (!user_mode(regs))
		goto no_context;
	pagefault_out_of_memory();
	return 0;

no_context:
	current->thread.signo = SIGBUS;
	current->thread.faddr = address;
	return send_fault_sig(regs);

bus_err:
	current->thread.signo = SIGBUS;
	current->thread.code = BUS_ADRERR;
	current->thread.faddr = address;
	goto send_sig;

map_err:
	current->thread.signo = SIGSEGV;
	current->thread.code = SEGV_MAPERR;
	current->thread.faddr = address;
	goto send_sig;

acc_err:
	current->thread.signo = SIGSEGV;
	current->thread.code = SEGV_ACCERR;
	current->thread.faddr = address;

send_sig:
	up_read(&mm->mmap_sem);
	return send_fault_sig(regs);
}