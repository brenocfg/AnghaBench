#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
struct vm_map {int /*<<< orphan*/  pmap; } ;
struct trapframe {scalar_t__ tf_stval; scalar_t__ tf_scause; int* tf_a; scalar_t__ tf_sepc; } ;
struct thread {scalar_t__ td_critnest; scalar_t__ td_intr_nesting_level; struct proc* td_proc; struct pcb* td_pcb; } ;
struct proc {TYPE_1__* p_vmspace; } ;
struct pcb {scalar_t__ pcb_onfault; } ;
struct TYPE_2__ {struct vm_map vm_map; } ;

/* Variables and functions */
 scalar_t__ EXCP_FAULT_STORE ; 
 scalar_t__ EXCP_INST_PAGE_FAULT ; 
 scalar_t__ EXCP_STORE_PAGE_FAULT ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_FAULT_NORMAL ; 
 scalar_t__ VM_MAX_USER_ADDRESS ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 scalar_t__ WITNESS_CHECK (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  call_trapsignal (struct thread*,int,int,void*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dump_regs (struct trapframe*) ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  kdb_reenter () ; 
 struct vm_map* kernel_map ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_fault_fixup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 
 int vm_fault_trap (struct vm_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
data_abort(struct trapframe *frame, int usermode)
{
	struct vm_map *map;
	uint64_t stval;
	struct thread *td;
	struct pcb *pcb;
	vm_prot_t ftype;
	vm_offset_t va;
	struct proc *p;
	int error, sig, ucode;

#ifdef KDB
	if (kdb_active) {
		kdb_reenter();
		return;
	}
#endif

	td = curthread;
	p = td->td_proc;
	pcb = td->td_pcb;
	stval = frame->tf_stval;

	if (td->td_critnest != 0 || td->td_intr_nesting_level != 0 ||
	    WITNESS_CHECK(WARN_SLEEPOK | WARN_GIANTOK, NULL,
	    "Kernel page fault") != 0)
		goto fatal;

	if (usermode)
		map = &td->td_proc->p_vmspace->vm_map;
	else if (stval >= VM_MAX_USER_ADDRESS)
		map = kernel_map;
	else {
		if (pcb->pcb_onfault == 0)
			goto fatal;
		map = &td->td_proc->p_vmspace->vm_map;
	}

	va = trunc_page(stval);

	if ((frame->tf_scause == EXCP_FAULT_STORE) ||
	    (frame->tf_scause == EXCP_STORE_PAGE_FAULT)) {
		ftype = VM_PROT_WRITE;
	} else if (frame->tf_scause == EXCP_INST_PAGE_FAULT) {
		ftype = VM_PROT_EXECUTE;
	} else {
		ftype = VM_PROT_READ;
	}

	if (pmap_fault_fixup(map->pmap, va, ftype))
		goto done;

	error = vm_fault_trap(map, va, ftype, VM_FAULT_NORMAL, &sig, &ucode);
	if (error != KERN_SUCCESS) {
		if (usermode) {
			call_trapsignal(td, sig, ucode, (void *)stval);
		} else {
			if (pcb->pcb_onfault != 0) {
				frame->tf_a[0] = error;
				frame->tf_sepc = pcb->pcb_onfault;
				return;
			}
			goto fatal;
		}
	}

done:
	if (usermode)
		userret(td, frame);
	return;

fatal:
	dump_regs(frame);
	panic("Fatal page fault at %#lx: %#016lx", frame->tf_sepc, stval);
}