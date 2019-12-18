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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int tf_cs; int tf_eip; int tf_err; long tf_eax; int /*<<< orphan*/  tf_edx; scalar_t__ tf_esp; } ;
struct syscall_args {long code; int narg; scalar_t__ args; TYPE_2__* callp; } ;
struct thread {int /*<<< orphan*/ * td_retval; struct syscall_args td_sa; struct trapframe* td_frame; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; } ;
typedef  int /*<<< orphan*/  quad_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_4__ {int sy_narg; } ;
struct TYPE_3__ {long sv_size; TYPE_2__* sv_table; } ;

/* Variables and functions */
 int EFAULT ; 
 long SYS___syscall ; 
 long SYS_syscall ; 
 scalar_t__ __predict_false (int) ; 
 int copyin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fueword (int /*<<< orphan*/ *,long*) ; 
 int fueword32 (void*,int*) ; 
 int fuword16 (void*) ; 

int
cpu_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	struct trapframe *frame;
	struct syscall_args *sa;
	caddr_t params;
	long tmp;
	int error;
#ifdef COMPAT_43
	u_int32_t eip;
	int cs;
#endif

	p = td->td_proc;
	frame = td->td_frame;
	sa = &td->td_sa;

#ifdef COMPAT_43
	if (__predict_false(frame->tf_cs == 7 && frame->tf_eip == 2)) {
		/*
		 * In lcall $7,$0 after int $0x80.  Convert the user
		 * frame to what it would be for a direct int 0x80 instead
		 * of lcall $7,$0, by popping the lcall return address.
		 */
		error = fueword32((void *)frame->tf_esp, &eip);
		if (error == -1)
			return (EFAULT);
		cs = fuword16((void *)(frame->tf_esp + sizeof(u_int32_t)));
		if (cs == -1)
			return (EFAULT);

		/*
		 * Unwind in-kernel frame after all stack frame pieces
		 * were successfully read.
		 */
		frame->tf_eip = eip;
		frame->tf_cs = cs;
		frame->tf_esp += 2 * sizeof(u_int32_t);
		frame->tf_err = 7;	/* size of lcall $7,$0 */
	}
#endif

	sa->code = frame->tf_eax;
	params = (caddr_t)frame->tf_esp + sizeof(uint32_t);

	/*
	 * Need to check if this is a 32 bit or 64 bit syscall.
	 */
	if (sa->code == SYS_syscall) {
		/*
		 * Code is first argument, followed by actual args.
		 */
		error = fueword(params, &tmp);
		if (error == -1)
			return (EFAULT);
		sa->code = tmp;
		params += sizeof(uint32_t);
	} else if (sa->code == SYS___syscall) {
		/*
		 * Like syscall, but code is a quad, so as to maintain
		 * quad alignment for the rest of the arguments.
		 */
		error = fueword(params, &tmp);
		if (error == -1)
			return (EFAULT);
		sa->code = tmp;
		params += sizeof(quad_t);
	}

 	if (sa->code >= p->p_sysent->sv_size)
 		sa->callp = &p->p_sysent->sv_table[0];
  	else
 		sa->callp = &p->p_sysent->sv_table[sa->code];
	sa->narg = sa->callp->sy_narg;

	if (params != NULL && sa->narg != 0)
		error = copyin(params, (caddr_t)sa->args,
		    (u_int)(sa->narg * sizeof(uint32_t)));
	else
		error = 0;

	if (error == 0) {
		td->td_retval[0] = 0;
		td->td_retval[1] = frame->tf_edx;
	}
		
	return (error);
}