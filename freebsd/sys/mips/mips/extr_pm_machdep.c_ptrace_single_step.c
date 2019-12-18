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
struct trapframe {uintptr_t pc; int cause; int /*<<< orphan*/  fsr; } ;
struct TYPE_2__ {uintptr_t md_ss_addr; int md_ss_instr; } ;
struct thread {TYPE_1__ td_md; int /*<<< orphan*/  td_tid; struct proc* td_proc; struct trapframe* td_frame; } ;
struct proc {char* p_comm; int p_pid; } ;
typedef  uintptr_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,uintptr_t,int) ; 
 int EFAULT ; 
 int /*<<< orphan*/  KTR_PTRACE ; 
 int MIPS_BREAK_SSTEP ; 
 int MIPS_CR_BR_DELAY ; 
 uintptr_t MipsEmulateBranch (struct trapframe*,uintptr_t,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,void*,void*) ; 
 int ptrace_read_int (struct thread*,uintptr_t,int*) ; 
 int ptrace_write_int (struct thread*,uintptr_t,int) ; 

int
ptrace_single_step(struct thread *td)
{
	uintptr_t va;
	struct trapframe *locr0 = td->td_frame;
	int error;
	int bpinstr = MIPS_BREAK_SSTEP;
	int curinstr;
	struct proc *p;

	p = td->td_proc;
	PROC_UNLOCK(p);
	/*
	 * Fetch what's at the current location.
	 */
	error = ptrace_read_int(td, locr0->pc, &curinstr);
	if (error)
		goto out;

	CTR3(KTR_PTRACE,
	    "ptrace_single_step: tid %d, current instr at %#lx: %#08x",
	    td->td_tid, locr0->pc, curinstr);

	/* compute next address after current location */
	if (locr0->cause & MIPS_CR_BR_DELAY) {
		va = MipsEmulateBranch(locr0, locr0->pc, locr0->fsr,
		    (uintptr_t)&curinstr);
	} else {
		va = locr0->pc + 4;
	}
	if (td->td_md.md_ss_addr) {
		printf("SS %s (%d): breakpoint already set at %p (va %p)\n",
		    p->p_comm, p->p_pid, (void *)td->td_md.md_ss_addr,
		    (void *)va); /* XXX */
		error = EFAULT;
		goto out;
	}
	td->td_md.md_ss_addr = va;
	/*
	 * Fetch what's at the current location.
	 */
	error = ptrace_read_int(td, (off_t)va, &td->td_md.md_ss_instr);
	if (error)
		goto out;

	/*
	 * Store breakpoint instruction at the "next" location now.
	 */
	error = ptrace_write_int(td, va, bpinstr);

	/*
	 * The sync'ing of I & D caches is done by proc_rwmem()
	 * through proc_writemem().
	 */

out:
	PROC_LOCK(p);
	if (error == 0)
		CTR3(KTR_PTRACE,
		    "ptrace_single_step: tid %d, break set at %#lx: (%#08x)",
		    td->td_tid, va, td->td_md.md_ss_instr); 
	return (error);
}