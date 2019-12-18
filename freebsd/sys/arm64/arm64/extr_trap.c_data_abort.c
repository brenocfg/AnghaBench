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
typedef  int vm_prot_t ;
typedef  scalar_t__ uint64_t ;
struct vm_map {int /*<<< orphan*/  pmap; } ;
struct trapframe {int* tf_x; scalar_t__ tf_elr; } ;
struct TYPE_4__ {scalar_t__ md_spinlock_count; } ;
struct thread {scalar_t__ td_critnest; scalar_t__ td_intr_nesting_level; TYPE_2__ td_md; struct proc* td_proc; struct pcb* td_pcb; } ;
struct proc {TYPE_1__* p_vmspace; } ;
struct pcb {scalar_t__ pcb_onfault; } ;
struct TYPE_3__ {struct vm_map vm_map; } ;

/* Variables and functions */
 int ESR_ELx_EXCEPTION (scalar_t__) ; 
#define  EXCP_INSN_ABORT 129 
#define  EXCP_INSN_ABORT_L 128 
 scalar_t__ ISS_DATA_WnR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KDB_WHY_TRAP ; 
 int /*<<< orphan*/  KDB_WHY_UNSET ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_FAULT_NORMAL ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 scalar_t__ WITNESS_CHECK (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  call_trapsignal (struct thread*,int,int,void*) ; 
 int /*<<< orphan*/  clrex () ; 
 scalar_t__ debugger_on_trap ; 
 int /*<<< orphan*/  intr_enable () ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  kdb_reenter () ; 
 int kdb_trap (int,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  kdb_why ; 
 struct vm_map* kernel_map ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int pmap_fault (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  print_registers (struct trapframe*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 
 int vm_fault_trap (struct vm_map*,scalar_t__,int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
data_abort(struct thread *td, struct trapframe *frame, uint64_t esr,
    uint64_t far, int lower)
{
	struct vm_map *map;
	struct proc *p;
	struct pcb *pcb;
	vm_prot_t ftype;
	int error, sig, ucode;
#ifdef KDB
	bool handled;
#endif

	/*
	 * According to the ARMv8-A rev. A.g, B2.10.5 "Load-Exclusive
	 * and Store-Exclusive instruction usage restrictions", state
	 * of the exclusive monitors after data abort exception is unknown.
	 */
	clrex();

#ifdef KDB
	if (kdb_active) {
		kdb_reenter();
		return;
	}
#endif

	pcb = td->td_pcb;
	p = td->td_proc;
	if (lower)
		map = &p->p_vmspace->vm_map;
	else {
		intr_enable();

		/* The top bit tells us which range to use */
		if (far >= VM_MAXUSER_ADDRESS) {
			map = kernel_map;
		} else {
			map = &p->p_vmspace->vm_map;
			if (map == NULL)
				map = kernel_map;
		}
	}

	/*
	 * Try to handle translation, access flag, and permission faults.
	 * Translation faults may occur as a result of the required
	 * break-before-make sequence used when promoting or demoting
	 * superpages.  Such faults must not occur while holding the pmap lock,
	 * or pmap_fault() will recurse on that lock.
	 */
	if ((lower || map == kernel_map || pcb->pcb_onfault != 0) &&
	    pmap_fault(map->pmap, esr, far) == KERN_SUCCESS)
		return;

	KASSERT(td->td_md.md_spinlock_count == 0,
	    ("data abort with spinlock held"));
	if (td->td_critnest != 0 || WITNESS_CHECK(WARN_SLEEPOK |
	    WARN_GIANTOK, NULL, "Kernel page fault") != 0) {
		print_registers(frame);
		printf(" far: %16lx\n", far);
		printf(" esr:         %.8lx\n", esr);
		panic("data abort in critical section or under mutex");
	}

	switch (ESR_ELx_EXCEPTION(esr)) {
	case EXCP_INSN_ABORT:
	case EXCP_INSN_ABORT_L:
		ftype = VM_PROT_EXECUTE;
		break;
	default:
		ftype = (esr & ISS_DATA_WnR) == 0 ? VM_PROT_READ :
		    VM_PROT_READ | VM_PROT_WRITE;
		break;
	}

	/* Fault in the page. */
	error = vm_fault_trap(map, far, ftype, VM_FAULT_NORMAL, &sig, &ucode);
	if (error != KERN_SUCCESS) {
		if (lower) {
			call_trapsignal(td, sig, ucode, (void *)far);
		} else {
			if (td->td_intr_nesting_level == 0 &&
			    pcb->pcb_onfault != 0) {
				frame->tf_x[0] = error;
				frame->tf_elr = pcb->pcb_onfault;
				return;
			}

			printf("Fatal data abort:\n");
			print_registers(frame);
			printf(" far: %16lx\n", far);
			printf(" esr:         %.8lx\n", esr);

#ifdef KDB
			if (debugger_on_trap) {
				kdb_why = KDB_WHY_TRAP;
				handled = kdb_trap(ESR_ELx_EXCEPTION(esr), 0,
				    frame);
				kdb_why = KDB_WHY_UNSET;
				if (handled)
					return;
			}
#endif
			panic("vm_fault failed: %lx", frame->tf_elr);
		}
	}

	if (lower)
		userret(td, frame);
}