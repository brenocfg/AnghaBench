#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct trapframe {scalar_t__* fixreg; int cr; int srr0; } ;
struct thread {int* td_retval; struct trapframe* td_frame; struct proc* td_proc; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
#define  ERESTART 128 
 int FIRSTARG ; 
 int SV_ABI_ERRNO (struct proc*,int) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ SYS___syscall ; 
 int SYS_freebsd6_lseek ; 
 int SYS_lseek ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{
	struct proc *p;
	struct trapframe *tf;
	int fixup;

	if (error == EJUSTRETURN)
		return;

	p = td->td_proc;
	tf = td->td_frame;

	if (tf->fixreg[0] == SYS___syscall &&
	    (SV_PROC_FLAG(p, SV_ILP32))) {
		int code = tf->fixreg[FIRSTARG + 1];
		fixup = (
#if defined(COMPAT_FREEBSD6) && defined(SYS_freebsd6_lseek)
		    code != SYS_freebsd6_lseek &&
#endif
		    code != SYS_lseek) ?  1 : 0;
	} else
		fixup = 0;

	switch (error) {
	case 0:
		if (fixup) {
			/*
			 * 64-bit return, 32-bit syscall. Fixup byte order
			 */
			tf->fixreg[FIRSTARG] = 0;
			tf->fixreg[FIRSTARG + 1] = td->td_retval[0];
		} else {
			tf->fixreg[FIRSTARG] = td->td_retval[0];
			tf->fixreg[FIRSTARG + 1] = td->td_retval[1];
		}
		tf->cr &= ~0x10000000;		/* Unset summary overflow */
		break;
	case ERESTART:
		/*
		 * Set user's pc back to redo the system call.
		 */
		tf->srr0 -= 4;
		break;
	default:
		tf->fixreg[FIRSTARG] = SV_ABI_ERRNO(p, error);
		tf->cr |= 0x10000000;		/* Set summary overflow */
		break;
	}
}