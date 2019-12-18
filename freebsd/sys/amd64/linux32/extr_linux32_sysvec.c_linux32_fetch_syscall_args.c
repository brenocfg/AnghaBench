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
struct trapframe {size_t tf_rax; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rbx; } ;
struct syscall_args {size_t code; TYPE_2__* callp; int /*<<< orphan*/  narg; int /*<<< orphan*/ * args; } ;
struct thread {int /*<<< orphan*/ * td_retval; struct syscall_args td_sa; struct trapframe* td_frame; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; } ;
struct TYPE_4__ {int /*<<< orphan*/  sy_narg; } ;
struct TYPE_3__ {size_t sv_size; TYPE_2__* sv_table; } ;

/* Variables and functions */

__attribute__((used)) static int
linux32_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	struct trapframe *frame;
	struct syscall_args *sa;

	p = td->td_proc;
	frame = td->td_frame;
	sa = &td->td_sa;

	sa->args[0] = frame->tf_rbx;
	sa->args[1] = frame->tf_rcx;
	sa->args[2] = frame->tf_rdx;
	sa->args[3] = frame->tf_rsi;
	sa->args[4] = frame->tf_rdi;
	sa->args[5] = frame->tf_rbp;	/* Unconfirmed */
	sa->code = frame->tf_rax;

	if (sa->code >= p->p_sysent->sv_size)
		/* nosys */
		sa->callp = &p->p_sysent->sv_table[p->p_sysent->sv_size - 1];
	else
		sa->callp = &p->p_sysent->sv_table[sa->code];
	sa->narg = sa->callp->sy_narg;

	td->td_retval[0] = 0;
	td->td_retval[1] = frame->tf_rdx;

	return (0);
}