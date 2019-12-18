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
typedef  void* u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int tf_cs; int tf_rip; int tf_err; size_t tf_rax; int /*<<< orphan*/  tf_rdx; scalar_t__ tf_rsp; } ;
struct syscall_args {size_t code; int narg; void** args; TYPE_2__* callp; } ;
struct thread {int /*<<< orphan*/ * td_retval; struct syscall_args td_sa; struct trapframe* td_frame; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; } ;
typedef  int /*<<< orphan*/  quad_t ;
typedef  void* caddr_t ;
struct TYPE_4__ {int sy_narg; } ;
struct TYPE_3__ {size_t sv_size; TYPE_2__* sv_table; } ;

/* Variables and functions */
 int EFAULT ; 
 size_t SYS___syscall ; 
 size_t SYS_syscall ; 
 scalar_t__ __predict_false (int) ; 
 int copyin (void*,void*,int /*<<< orphan*/ ) ; 
 int fueword32 (void*,void**) ; 
 int fuword16 (void*) ; 

int
ia32_fetch_syscall_args(struct thread *td)
{
	struct proc *p;
	struct trapframe *frame;
	struct syscall_args *sa;
	caddr_t params;
	u_int32_t args[8], tmp;
	int error, i;
#ifdef COMPAT_43
	u_int32_t eip;
	int cs;
#endif

	p = td->td_proc;
	frame = td->td_frame;
	sa = &td->td_sa;

#ifdef COMPAT_43
	if (__predict_false(frame->tf_cs == 7 && frame->tf_rip == 2)) {
		/*
		 * In lcall $7,$0 after int $0x80.  Convert the user
		 * frame to what it would be for a direct int 0x80 instead
		 * of lcall $7,$0, by popping the lcall return address.
		 */
		error = fueword32((void *)frame->tf_rsp, &eip);
		if (error == -1)
			return (EFAULT);
		cs = fuword16((void *)(frame->tf_rsp + sizeof(u_int32_t)));
		if (cs == -1)
			return (EFAULT);

		/*
		 * Unwind in-kernel frame after all stack frame pieces
		 * were successfully read.
		 */
		frame->tf_rip = eip;
		frame->tf_cs = cs;
		frame->tf_rsp += 2 * sizeof(u_int32_t);
		frame->tf_err = 7;		/* size of lcall $7,$0 */
	}
#endif

	params = (caddr_t)frame->tf_rsp + sizeof(u_int32_t);
	sa->code = frame->tf_rax;

	/*
	 * Need to check if this is a 32 bit or 64 bit syscall.
	 */
	if (sa->code == SYS_syscall) {
		/*
		 * Code is first argument, followed by actual args.
		 */
		error = fueword32(params, &tmp);
		if (error == -1)
			return (EFAULT);
		sa->code = tmp;
		params += sizeof(int);
	} else if (sa->code == SYS___syscall) {
		/*
		 * Like syscall, but code is a quad, so as to maintain
		 * quad alignment for the rest of the arguments.
		 * We use a 32-bit fetch in case params is not
		 * aligned.
		 */
		error = fueword32(params, &tmp);
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
		error = copyin(params, (caddr_t)args,
		    (u_int)(sa->narg * sizeof(int)));
	else
		error = 0;

	for (i = 0; i < sa->narg; i++)
		sa->args[i] = args[i];

	if (error == 0) {
		td->td_retval[0] = 0;
		td->td_retval[1] = frame->tf_rdx;
	}

	return (error);
}