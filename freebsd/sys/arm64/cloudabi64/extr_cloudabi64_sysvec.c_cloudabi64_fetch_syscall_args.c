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
struct trapframe {size_t* tf_x; } ;
struct syscall_args {size_t code; size_t* args; TYPE_1__* callp; int /*<<< orphan*/  narg; } ;
struct thread {size_t* td_retval; struct syscall_args td_sa; struct trapframe* td_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  sy_narg; } ;

/* Variables and functions */
 size_t CLOUDABI64_SYS_MAXSYSCALL ; 
 int ENOSYS ; 
 int MAXARGS ; 
 TYPE_1__* cloudabi64_sysent ; 

__attribute__((used)) static int
cloudabi64_fetch_syscall_args(struct thread *td)
{
	struct trapframe *frame;
	struct syscall_args *sa;
	int i;

	frame = td->td_frame;
	sa = &td->td_sa;

	/* Obtain system call number. */
	sa->code = frame->tf_x[8];
	if (sa->code >= CLOUDABI64_SYS_MAXSYSCALL)
		return (ENOSYS);
	sa->callp = &cloudabi64_sysent[sa->code];
	sa->narg = sa->callp->sy_narg;

	/* Fetch system call arguments. */
	for (i = 0; i < MAXARGS; i++)
		sa->args[i] = frame->tf_x[i];

	/* Default system call return values. */
	td->td_retval[0] = 0;
	td->td_retval[1] = frame->tf_x[1];
	return (0);
}