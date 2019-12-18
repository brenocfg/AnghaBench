#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  scalar_t__ u_long ;
struct trapframe {int tf_type; int tf_tstate; scalar_t__ tf_tpc; scalar_t__ tf_tnpc; int /*<<< orphan*/  tf_tar; } ;
struct thread {struct proc* td_proc; int /*<<< orphan*/ * td_pcb; } ;
struct proc {TYPE_2__* p_vmspace; } ;
struct TYPE_7__ {int eflags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pm_context; } ;
struct TYPE_6__ {int /*<<< orphan*/  vm_map; TYPE_1__ vm_pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  KTR_TRAP ; 
 int MAP_ENTRY_NOFAULT ; 
 scalar_t__ TLB_CTX_KERNEL ; 
 scalar_t__ TLB_TAR_CTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLB_TAR_VA (int /*<<< orphan*/ ) ; 
 int TSTATE_PRIV ; 
 int T_DATA_MISS ; 
 int T_DATA_PROTECTION ; 
 int T_KERNEL ; 
 int /*<<< orphan*/  VM_FAULT_NORMAL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 scalar_t__ copy_fault ; 
 scalar_t__ copy_nofault_begin ; 
 scalar_t__ copy_nofault_end ; 
 size_t curcpu ; 
 scalar_t__ fs_fault ; 
 scalar_t__ fs_nofault_begin ; 
 scalar_t__ fs_nofault_end ; 
 int /*<<< orphan*/ * kernel_map ; 
 int vm_fault_trap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  vm_map_lock_read (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_map_lookup_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  vm_map_unlock_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
trap_pfault(struct thread *td, struct trapframe *tf, int *signo, int *ucode)
{
	vm_map_t map;
	struct proc *p;
	vm_offset_t va;
	vm_prot_t prot;
	vm_map_entry_t entry;
	u_long ctx;
	int type;
	int rv;

	if (td == NULL)
		return (-1);
	KASSERT(td->td_pcb != NULL, ("trap_pfault: pcb NULL"));
	KASSERT(td->td_proc != NULL, ("trap_pfault: curproc NULL"));
	KASSERT(td->td_proc->p_vmspace != NULL, ("trap_pfault: vmspace NULL"));

	p = td->td_proc;

	rv = KERN_SUCCESS;
	ctx = TLB_TAR_CTX(tf->tf_tar);
	type = tf->tf_type & ~T_KERNEL;
	va = TLB_TAR_VA(tf->tf_tar);

	CTR4(KTR_TRAP, "trap_pfault: td=%p pm_ctx=%#lx va=%#lx ctx=%#lx",
	    td, p->p_vmspace->vm_pmap.pm_context[curcpu], va, ctx);

	if (type == T_DATA_PROTECTION)
		prot = VM_PROT_WRITE;
	else {
		if (type == T_DATA_MISS)
			prot = VM_PROT_READ;
		else
			prot = VM_PROT_READ | VM_PROT_EXECUTE;
	}

	if (ctx != TLB_CTX_KERNEL) {
		/* This is a fault on non-kernel virtual memory. */
		map = &p->p_vmspace->vm_map;
	} else {
		/*
		 * This is a fault on kernel virtual memory.  Attempts to
		 * access kernel memory from user mode cause privileged
		 * action traps, not page fault.
		 */
		KASSERT(tf->tf_tstate & TSTATE_PRIV,
		    ("trap_pfault: fault on nucleus context from user mode"));

		if (tf->tf_tpc >= (u_long)copy_nofault_begin &&
		    tf->tf_tpc <= (u_long)copy_nofault_end) {
			vm_map_lock_read(kernel_map);
			if (vm_map_lookup_entry(kernel_map, va, &entry) &&
			    (entry->eflags & MAP_ENTRY_NOFAULT) != 0) {
				tf->tf_tpc = (u_long)copy_fault;
				tf->tf_tnpc = tf->tf_tpc + 4;
				vm_map_unlock_read(kernel_map);
				return (0);
			}
			vm_map_unlock_read(kernel_map);
		}
		map = kernel_map;
	}

	/* Fault in the page. */
	rv = vm_fault_trap(map, va, prot, VM_FAULT_NORMAL, signo, ucode);

	CTR3(KTR_TRAP, "trap_pfault: return td=%p va=%#lx rv=%d",
	    td, va, rv);
	if (rv == KERN_SUCCESS)
		return (true);
	if (ctx != TLB_CTX_KERNEL && (tf->tf_tstate & TSTATE_PRIV) != 0) {
		if (tf->tf_tpc >= (u_long)fs_nofault_begin &&
		    tf->tf_tpc <= (u_long)fs_nofault_end) {
			tf->tf_tpc = (u_long)fs_fault;
			tf->tf_tnpc = tf->tf_tpc + 4;
			return (true);
		}
		if (tf->tf_tpc >= (u_long)copy_nofault_begin &&
		    tf->tf_tpc <= (u_long)copy_nofault_end) {
			tf->tf_tpc = (u_long)copy_fault;
			tf->tf_tnpc = tf->tf_tpc + 4;
			return (true);
		}
	}
	return (false);
}