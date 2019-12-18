#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
struct TYPE_6__ {int dsisr; } ;
struct TYPE_5__ {int esr; } ;
struct TYPE_7__ {TYPE_2__ aim; TYPE_1__ booke; } ;
struct trapframe {scalar_t__ exc; int srr1; TYPE_3__ cpu; int /*<<< orphan*/  dar; int /*<<< orphan*/  srr0; } ;
struct thread {struct proc* td_proc; } ;
struct proc {TYPE_4__* p_vmspace; } ;
struct TYPE_8__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int DSISR_STORE ; 
 int ESR_ST ; 
 scalar_t__ EXC_ISI ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int KERN_SUCCESS ; 
 int SRR1_ISI_PFAULT ; 
 int /*<<< orphan*/  VM_FAULT_NORMAL ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 struct thread* curthread ; 
 scalar_t__ handle_onfault (struct trapframe*) ; 
 int /*<<< orphan*/ * kernel_map ; 
 int pmap_decode_kernel_ptr (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int vm_fault_trap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static bool
trap_pfault(struct trapframe *frame, bool user, int *signo, int *ucode)
{
	vm_offset_t	eva;
	struct		thread *td;
	struct		proc *p;
	vm_map_t	map;
	vm_prot_t	ftype;
	int		rv, is_user;

	td = curthread;
	p = td->td_proc;
	if (frame->exc == EXC_ISI) {
		eva = frame->srr0;
		ftype = VM_PROT_EXECUTE;
		if (frame->srr1 & SRR1_ISI_PFAULT)
			ftype |= VM_PROT_READ;
	} else {
		eva = frame->dar;
#ifdef BOOKE
		if (frame->cpu.booke.esr & ESR_ST)
#else
		if (frame->cpu.aim.dsisr & DSISR_STORE)
#endif
			ftype = VM_PROT_WRITE;
		else
			ftype = VM_PROT_READ;
	}

	if (user) {
		KASSERT(p->p_vmspace != NULL, ("trap_pfault: vmspace  NULL"));
		map = &p->p_vmspace->vm_map;
	} else {
		rv = pmap_decode_kernel_ptr(eva, &is_user, &eva);
		if (rv != 0)
			return (false);

		if (is_user)
			map = &p->p_vmspace->vm_map;
		else
			map = kernel_map;
	}

	/* Fault in the page. */
	rv = vm_fault_trap(map, eva, ftype, VM_FAULT_NORMAL, signo, ucode);
	/*
	 * XXXDTRACE: add dtrace_doubletrap_func here?
	 */

	if (rv == KERN_SUCCESS)
		return (true);

	if (!user && handle_onfault(frame))
		return (true);

	return (false);
}