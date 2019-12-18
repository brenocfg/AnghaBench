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
struct trapframe {size_t tf_rax; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; } ;
struct syscall_args {size_t code; int /*<<< orphan*/ * args; TYPE_1__* callp; int /*<<< orphan*/  narg; } ;
struct thread {int /*<<< orphan*/ * td_retval; struct syscall_args td_sa; struct trapframe* td_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  sy_narg; } ;

/* Variables and functions */
 size_t CLOUDABI64_SYS_MAXSYSCALL ; 
 int ENOSYS ; 
 TYPE_1__* cloudabi64_sysent ; 

__attribute__((used)) static int
cloudabi64_fetch_syscall_args(struct thread *td)
{
	struct trapframe *frame;
	struct syscall_args *sa;

	frame = td->td_frame;
	sa = &td->td_sa;

	/* Obtain system call number. */
	sa->code = frame->tf_rax;
	if (sa->code >= CLOUDABI64_SYS_MAXSYSCALL)
		return (ENOSYS);
	sa->callp = &cloudabi64_sysent[sa->code];
	sa->narg = sa->callp->sy_narg;

	/* Fetch system call arguments. */
	sa->args[0] = frame->tf_rdi;
	sa->args[1] = frame->tf_rsi;
	sa->args[2] = frame->tf_rdx;
	sa->args[3] = frame->tf_rcx; /* Actually %r10. */
	sa->args[4] = frame->tf_r8;
	sa->args[5] = frame->tf_r9;

	/* Default system call return values. */
	td->td_retval[0] = 0;
	td->td_retval[1] = frame->tf_rdx;
	return (0);
}