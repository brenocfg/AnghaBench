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
struct syscall_args {size_t code; int nap; int narg; scalar_t__ args; TYPE_2__* callp; } ;
struct thread {scalar_t__* td_retval; TYPE_3__* td_frame; struct proc* td_proc; struct syscall_args td_sa; } ;
struct proc {TYPE_1__* p_sysent; } ;
typedef  size_t register_t ;
struct TYPE_6__ {size_t tf_r7; size_t tf_r0; scalar_t__ tf_usr_sp; } ;
struct TYPE_5__ {int sy_narg; } ;
struct TYPE_4__ {size_t sv_size; TYPE_2__* sv_table; } ;

/* Variables and functions */
 size_t SYS___syscall ; 
 size_t SYS_syscall ; 
 size_t _QUAD_LOWWORD ; 
 int copyin (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,size_t*,int) ; 

int
cpu_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	register_t *ap;
	struct syscall_args *sa;
	int error;

	sa = &td->td_sa;
	sa->code = td->td_frame->tf_r7;
	ap = &td->td_frame->tf_r0;
	if (sa->code == SYS_syscall) {
		sa->code = *ap++;
		sa->nap--;
	} else if (sa->code == SYS___syscall) {
		sa->code = ap[_QUAD_LOWWORD];
		sa->nap -= 2;
		ap += 2;
	}
	p = td->td_proc;
	if (sa->code >= p->p_sysent->sv_size)
		sa->callp = &p->p_sysent->sv_table[0];
	else
		sa->callp = &p->p_sysent->sv_table[sa->code];
	sa->narg = sa->callp->sy_narg;
	error = 0;
	memcpy(sa->args, ap, sa->nap * sizeof(register_t));
	if (sa->narg > sa->nap) {
		error = copyin((void *)td->td_frame->tf_usr_sp, sa->args +
		    sa->nap, (sa->narg - sa->nap) * sizeof(register_t));
	}
	if (error == 0) {
		td->td_retval[0] = 0;
		td->td_retval[1] = 0;
	}
	return (error);
}