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
struct TYPE_4__ {scalar_t__ md_ptrace_instr; scalar_t__ md_ptrace_instr_alt; int /*<<< orphan*/  md_ptrace_addr_alt; int /*<<< orphan*/  md_ptrace_addr; } ;
struct thread {TYPE_2__ td_md; struct proc* td_proc; TYPE_1__* td_frame; } ;
struct proc {int dummy; } ;
struct TYPE_3__ {int tf_spsr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int PSR_T ; 
 int /*<<< orphan*/  ptrace_write_int (struct thread*,int /*<<< orphan*/ ,scalar_t__) ; 

int
ptrace_clear_single_step(struct thread *td)
{
	struct proc *p;

	/* TODO: This needs to be updated for Thumb-2 */
	if ((td->td_frame->tf_spsr & PSR_T) != 0)
		return (EINVAL);

	if (td->td_md.md_ptrace_instr != 0) {
		p = td->td_proc;
		PROC_UNLOCK(p);
		ptrace_write_int(td, td->td_md.md_ptrace_addr,
		    td->td_md.md_ptrace_instr);
		PROC_LOCK(p);
		td->td_md.md_ptrace_instr = 0;
	}

	if (td->td_md.md_ptrace_instr_alt != 0) {
		p = td->td_proc;
		PROC_UNLOCK(p);
		ptrace_write_int(td, td->td_md.md_ptrace_addr_alt,
		    td->td_md.md_ptrace_instr_alt);
		PROC_LOCK(p);
		td->td_md.md_ptrace_instr_alt = 0;
	}

	return (0);
}