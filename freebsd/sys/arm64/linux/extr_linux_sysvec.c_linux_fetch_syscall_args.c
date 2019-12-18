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
struct syscall_args {size_t code; int narg; int /*<<< orphan*/  args; TYPE_3__* callp; } ;
struct thread {scalar_t__* td_retval; TYPE_1__* td_frame; struct syscall_args td_sa; struct proc* td_proc; } ;
struct proc {TYPE_2__* p_sysent; } ;
typedef  size_t register_t ;
struct TYPE_6__ {int sy_narg; } ;
struct TYPE_5__ {size_t sv_size; TYPE_3__* sv_table; } ;
struct TYPE_4__ {size_t* tf_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
linux_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	struct syscall_args *sa;
	register_t *ap;

	p = td->td_proc;
	ap = td->td_frame->tf_x;
	sa = &td->td_sa;

	sa->code = td->td_frame->tf_x[8];
	/* LINUXTODO: generic syscall? */
	if (sa->code >= p->p_sysent->sv_size)
		sa->callp = &p->p_sysent->sv_table[0];
	else
		sa->callp = &p->p_sysent->sv_table[sa->code];

	sa->narg = sa->callp->sy_narg;
	if (sa->narg > 8)
		panic("ARM64TODO: Could we have more than 8 args?");
	memcpy(sa->args, ap, 8 * sizeof(register_t));

	td->td_retval[0] = 0;
	return (0);
}