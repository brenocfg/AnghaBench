#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct vm_map {int /*<<< orphan*/  pmap; } ;
struct trapframe {scalar_t__ tf_pc; int tf_spsr; scalar_t__ tf_usr_lr; } ;
struct TYPE_4__ {scalar_t__ md_spinlock_count; } ;
struct thread {scalar_t__ td_cowgen; struct proc* td_proc; scalar_t__ td_pticks; TYPE_1__ td_md; struct trapframe* td_frame; } ;
struct proc {scalar_t__ p_cowgen; TYPE_2__* p_vmspace; } ;
struct ksig {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  traps; } ;
struct TYPE_5__ {struct vm_map vm_map; } ;

/* Variables and functions */
 scalar_t__ ARM_VECTORS_LOW ; 
 int KERN_SUCCESS ; 
 int PSR_F ; 
 int PSR_I ; 
 int SIGSEGV ; 
 scalar_t__ TRAP_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_FAULT_NORMAL ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 scalar_t__ VM_MIN_ADDRESS ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  call_trapsignal (struct thread*,int,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dab_fatal (struct trapframe*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct ksig*) ; 
 int /*<<< orphan*/  enable_interrupts (int) ; 
 int last_fault_code ; 
 scalar_t__ pmap_fault_fixup (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  printf (char*,void*,void*) ; 
 int /*<<< orphan*/  thread_cow_update (struct thread*) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 
 TYPE_3__ uvmexp ; 
 int /*<<< orphan*/  v_trap ; 
 scalar_t__ vector_page ; 
 int vm_fault_trap (struct vm_map*,scalar_t__,int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
prefetch_abort_handler(struct trapframe *tf)
{
	struct thread *td;
	struct proc * p;
	struct vm_map *map;
	vm_offset_t fault_pc, va;
	int error = 0, signo, ucode;
	struct ksig ksig;

#if 0
	/* Update vmmeter statistics */
	uvmexp.traps++;
#endif
#if 0
	printf("prefetch abort handler: %p %p\n", (void*)tf->tf_pc,
	    (void*)tf->tf_usr_lr);
#endif

 	td = curthread;
	p = td->td_proc;
	VM_CNT_INC(v_trap);

	if (TRAP_USERMODE(tf)) {
		td->td_frame = tf;
		if (td->td_cowgen != td->td_proc->p_cowgen)
			thread_cow_update(td);
	}
	fault_pc = tf->tf_pc;
	if (td->td_md.md_spinlock_count == 0) {
		if (__predict_true(tf->tf_spsr & PSR_I) == 0)
			enable_interrupts(PSR_I);
		if (__predict_true(tf->tf_spsr & PSR_F) == 0)
			enable_interrupts(PSR_F);
	}

	/* Prefetch aborts cannot happen in kernel mode */
	if (__predict_false(!TRAP_USERMODE(tf)))
		dab_fatal(tf, 0, tf->tf_pc, NULL, &ksig);
	td->td_pticks = 0;


	/* Ok validate the address, can only execute in USER space */
	if (__predict_false(fault_pc >= VM_MAXUSER_ADDRESS ||
	    (fault_pc < VM_MIN_ADDRESS && vector_page == ARM_VECTORS_LOW))) {
		signo = SIGSEGV;
		ucode = 0;
		goto do_trapsignal;
	}

	map = &td->td_proc->p_vmspace->vm_map;
	va = trunc_page(fault_pc);

	/*
	 * See if the pmap can handle this fault on its own...
	 */
#ifdef DEBUG
	last_fault_code = -1;
#endif
	if (pmap_fault_fixup(map->pmap, va, VM_PROT_READ, 1))
		goto out;

	error = vm_fault_trap(map, va, VM_PROT_READ | VM_PROT_EXECUTE,
	    VM_FAULT_NORMAL, &signo, &ucode);
	if (__predict_true(error == KERN_SUCCESS))
		goto out;

do_trapsignal:
	call_trapsignal(td, signo, ucode);

out:
	userret(td, tf);

}