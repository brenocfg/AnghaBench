#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct trapframe {int pc; int v0; int a0; int a1; int a2; int a3; int a4; int a5; int a6; int a7; int /*<<< orphan*/  v1; scalar_t__ sp; } ;
struct syscall_args {int* args; int code; int narg; TYPE_1__* callp; TYPE_3__* trapframe; } ;
struct thread {int /*<<< orphan*/ * td_retval; TYPE_4__* td_proc; TYPE_2__* td_pcb; struct syscall_args td_sa; struct trapframe* td_frame; } ;
struct sysentvec {int sv_size; TYPE_1__* sv_table; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {int p_pid; struct sysentvec* p_sysent; } ;
struct TYPE_7__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  cause; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcb_tpc; } ;
struct TYPE_5__ {int sy_narg; } ;

/* Variables and functions */
 scalar_t__ DELAYBRANCH (int /*<<< orphan*/ ) ; 
 int MipsEmulateBranch (struct trapframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (TYPE_4__*,int /*<<< orphan*/ ) ; 
#define  SYS___syscall 129 
#define  SYS_syscall 128 
 int /*<<< orphan*/  _QUAD_LOWWORD ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,size_t,int,...) ; 
 scalar_t__ trap_debug ; 

int
cpu_fetch_syscall_args(struct thread *td)
{
	struct trapframe *locr0;
	struct sysentvec *se;
	struct syscall_args *sa;
	int error, nsaved;

	locr0 = td->td_frame;
	sa = &td->td_sa;
	
	bzero(sa->args, sizeof(sa->args));

	/* compute next PC after syscall instruction */
	td->td_pcb->pcb_tpc = sa->trapframe->pc; /* Remember if restart */
	if (DELAYBRANCH(sa->trapframe->cause))	 /* Check BD bit */
		locr0->pc = MipsEmulateBranch(locr0, sa->trapframe->pc, 0, 0);
	else
		locr0->pc += sizeof(int);
	sa->code = locr0->v0;

	switch (sa->code) {
	case SYS___syscall:
	case SYS_syscall:
		/*
		 * This is an indirect syscall, in which the code is the first argument.
		 */
#if (!defined(__mips_n32) && !defined(__mips_n64)) || defined(COMPAT_FREEBSD32)
		if (sa->code == SYS___syscall && SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
			/*
			 * Like syscall, but code is a quad, so as to maintain alignment
			 * for the rest of the arguments.
			 */
			if (_QUAD_LOWWORD == 0)
				sa->code = locr0->a0;
			else
				sa->code = locr0->a1;
			sa->args[0] = locr0->a2;
			sa->args[1] = locr0->a3;
			nsaved = 2;
			break;
		} 
#endif
		/*
		 * This is either not a quad syscall, or is a quad syscall with a
		 * new ABI in which quads fit in a single register.
		 */
		sa->code = locr0->a0;
		sa->args[0] = locr0->a1;
		sa->args[1] = locr0->a2;
		sa->args[2] = locr0->a3;
		nsaved = 3;
#if defined(__mips_n32) || defined(__mips_n64)
#ifdef COMPAT_FREEBSD32
		if (!SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
#endif
			/*
			 * Non-o32 ABIs support more arguments in registers.
			 */
			sa->args[3] = locr0->a4;
			sa->args[4] = locr0->a5;
			sa->args[5] = locr0->a6;
			sa->args[6] = locr0->a7;
			nsaved += 4;
#ifdef COMPAT_FREEBSD32
		}
#endif
#endif
		break;
	default:
		/*
		 * A direct syscall, arguments are just parameters to the syscall.
		 */
		sa->args[0] = locr0->a0;
		sa->args[1] = locr0->a1;
		sa->args[2] = locr0->a2;
		sa->args[3] = locr0->a3;
		nsaved = 4;
#if defined (__mips_n32) || defined(__mips_n64)
#ifdef COMPAT_FREEBSD32
		if (!SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
#endif
			/*
			 * Non-o32 ABIs support more arguments in registers.
			 */
			sa->args[4] = locr0->a4;
			sa->args[5] = locr0->a5;
			sa->args[6] = locr0->a6;
			sa->args[7] = locr0->a7;
			nsaved += 4;
#ifdef COMPAT_FREEBSD32
		}
#endif
#endif
		break;
	}

#ifdef TRAP_DEBUG
	if (trap_debug)
		printf("SYSCALL #%d pid:%u\n", sa->code, td->td_proc->p_pid);
#endif

	se = td->td_proc->p_sysent;
	/*
	 * XXX
	 * Shouldn't this go before switching on the code?
	 */

	if (sa->code >= se->sv_size)
		sa->callp = &se->sv_table[0];
	else
		sa->callp = &se->sv_table[sa->code];

	sa->narg = sa->callp->sy_narg;

	if (sa->narg > nsaved) {
#if defined(__mips_n32) || defined(__mips_n64)
		/*
		 * XXX
		 * Is this right for new ABIs?  I think the 4 there
		 * should be 8, size there are 8 registers to skip,
		 * not 4, but I'm not certain.
		 */
#ifdef COMPAT_FREEBSD32
		if (!SV_PROC_FLAG(td->td_proc, SV_ILP32))
#endif
			printf("SYSCALL #%u pid:%u, narg (%u) > nsaved (%u).\n",
			    sa->code, td->td_proc->p_pid, sa->narg, nsaved);
#endif
#if (defined(__mips_n32) || defined(__mips_n64)) && defined(COMPAT_FREEBSD32)
		if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
			unsigned i;
			int32_t arg;

			error = 0; /* XXX GCC is awful.  */
			for (i = nsaved; i < sa->narg; i++) {
				error = copyin((caddr_t)(intptr_t)(locr0->sp +
				    (4 + (i - nsaved)) * sizeof(int32_t)),
				    (caddr_t)&arg, sizeof arg);
				if (error != 0)
					break;
				sa->args[i] = arg;
			}
		} else
#endif
		error = copyin((caddr_t)(intptr_t)(locr0->sp +
		    4 * sizeof(register_t)), (caddr_t)&sa->args[nsaved],
		   (u_int)(sa->narg - nsaved) * sizeof(register_t));
		if (error != 0) {
			locr0->v0 = error;
			locr0->a3 = 1;
		}
	} else
		error = 0;

	if (error == 0) {
		td->td_retval[0] = 0;
		td->td_retval[1] = locr0->v1;
	}

	return (error);
}