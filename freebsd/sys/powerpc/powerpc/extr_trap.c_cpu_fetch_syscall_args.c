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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int u_register_t ;
struct trapframe {size_t* fixreg; } ;
struct syscall_args {size_t code; int narg; int* args; TYPE_2__* callp; } ;
struct thread {size_t* td_retval; struct syscall_args td_sa; struct trapframe* td_frame; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; } ;
typedef  void* register_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {int sy_narg; } ;
struct TYPE_3__ {size_t sv_size; TYPE_2__* sv_table; } ;

/* Variables and functions */
 int FIRSTARG ; 
 int /*<<< orphan*/  MOREARGS (size_t) ; 
 int NARGREG ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (struct proc*,int /*<<< orphan*/ ) ; 
 size_t SYS___syscall ; 
 size_t SYS_syscall ; 
 int copyin (int /*<<< orphan*/ ,int*,int) ; 

int
cpu_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	struct trapframe *frame;
	struct syscall_args *sa;
	caddr_t	params;
	size_t argsz;
	int error, n, i;

	p = td->td_proc;
	frame = td->td_frame;
	sa = &td->td_sa;

	sa->code = frame->fixreg[0];
	params = (caddr_t)(frame->fixreg + FIRSTARG);
	n = NARGREG;

	if (sa->code == SYS_syscall) {
		/*
		 * code is first argument,
		 * followed by actual args.
		 */
		sa->code = *(register_t *) params;
		params += sizeof(register_t);
		n -= 1;
	} else if (sa->code == SYS___syscall) {
		/*
		 * Like syscall, but code is a quad,
		 * so as to maintain quad alignment
		 * for the rest of the args.
		 */
		if (SV_PROC_FLAG(p, SV_ILP32)) {
			params += sizeof(register_t);
			sa->code = *(register_t *) params;
			params += sizeof(register_t);
			n -= 2;
		} else {
			sa->code = *(register_t *) params;
			params += sizeof(register_t);
			n -= 1;
		}
	}

	if (sa->code >= p->p_sysent->sv_size)
		sa->callp = &p->p_sysent->sv_table[0];
	else
		sa->callp = &p->p_sysent->sv_table[sa->code];

	sa->narg = sa->callp->sy_narg;

	if (SV_PROC_FLAG(p, SV_ILP32)) {
		argsz = sizeof(uint32_t);

		for (i = 0; i < n; i++)
			sa->args[i] = ((u_register_t *)(params))[i] &
			    0xffffffff;
	} else {
		argsz = sizeof(uint64_t);

		for (i = 0; i < n; i++)
			sa->args[i] = ((u_register_t *)(params))[i];
	}

	if (sa->narg > n)
		error = copyin(MOREARGS(frame->fixreg[1]), sa->args + n,
			       (sa->narg - n) * argsz);
	else
		error = 0;

#ifdef __powerpc64__
	if (SV_PROC_FLAG(p, SV_ILP32) && sa->narg > n) {
		/* Expand the size of arguments copied from the stack */

		for (i = sa->narg; i >= n; i--)
			sa->args[i] = ((uint32_t *)(&sa->args[n]))[i-n];
	}
#endif

	if (error == 0) {
		td->td_retval[0] = 0;
		td->td_retval[1] = frame->fixreg[FIRSTARG + 1];
	}
	return (error);
}