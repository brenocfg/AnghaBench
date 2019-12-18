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
struct syscall_args {size_t code; int narg; unsigned int* args; TYPE_2__* callp; } ;
struct thread {scalar_t__* td_retval; TYPE_3__* td_frame; struct syscall_args td_sa; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; } ;
typedef  void* register_t ;
struct TYPE_6__ {void** tf_x; } ;
struct TYPE_5__ {int sy_narg; } ;
struct TYPE_4__ {size_t sv_size; TYPE_2__* sv_table; } ;

/* Variables and functions */
 size_t SYS___syscall ; 
 size_t SYS_syscall ; 
 int copyin (void*,unsigned int*,int) ; 
 int nitems (unsigned int*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
freebsd32_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	register_t *ap;
	struct syscall_args *sa;
	int error, i, nap;
	unsigned int args[4];

	nap = 4;
	p = td->td_proc;
	ap = td->td_frame->tf_x;
	sa = &td->td_sa;

	/* r7 is the syscall id */
	sa->code = td->td_frame->tf_x[7];

	if (sa->code == SYS_syscall) {
		sa->code = *ap++;
		nap--;
	} else if (sa->code == SYS___syscall) {
		sa->code = ap[1];
		nap -= 2;
		ap += 2;
	}

	if (sa->code >= p->p_sysent->sv_size)
		sa->callp = &p->p_sysent->sv_table[0];
	else
		sa->callp = &p->p_sysent->sv_table[sa->code];

	sa->narg = sa->callp->sy_narg;
	for (i = 0; i < nap; i++)
		sa->args[i] = ap[i];
	if (sa->narg > nap) {
		if ((sa->narg - nap) > nitems(args))
			panic("Too many system call arguiments");
		error = copyin((void *)td->td_frame->tf_x[13], args,
		    (sa->narg - nap) * sizeof(int));
		for (i = 0; i < (sa->narg - nap); i++)
			sa->args[i + nap] = args[i];
	}

	td->td_retval[0] = 0;
	td->td_retval[1] = 0;

	return (0);
}