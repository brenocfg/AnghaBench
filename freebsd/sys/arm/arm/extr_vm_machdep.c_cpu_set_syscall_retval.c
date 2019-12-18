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
typedef  scalar_t__ u_int ;
struct trapframe {scalar_t__ tf_r7; scalar_t__ tf_r0; scalar_t__ tf_r1; int tf_spsr; int /*<<< orphan*/  tf_pc; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_proc; struct trapframe* td_frame; } ;
typedef  scalar_t__ register_t ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  INSN_SIZE ; 
 int PSR_C ; 
 int PSR_T ; 
 scalar_t__ SV_ABI_ERRNO (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SYS___syscall ; 
 scalar_t__ SYS_lseek ; 
 int /*<<< orphan*/  THUMB_INSN_SIZE ; 
 size_t _QUAD_LOWWORD ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame;
	int fixup;
#ifdef __ARMEB__
	u_int call;
#endif

	frame = td->td_frame;
	fixup = 0;

#ifdef __ARMEB__
	/*
	 * __syscall returns an off_t while most other syscalls return an
	 * int. As an off_t is 64-bits and an int is 32-bits we need to
	 * place the returned data into r1. As the lseek and freebsd6_lseek
	 * syscalls also return an off_t they do not need this fixup.
	 */
	call = frame->tf_r7;
	if (call == SYS___syscall) {
		register_t *ap = &frame->tf_r0;
		register_t code = ap[_QUAD_LOWWORD];
		fixup = (code != SYS_lseek);
	}
#endif

	switch (error) {
	case 0:
		if (fixup) {
			frame->tf_r0 = 0;
			frame->tf_r1 = td->td_retval[0];
		} else {
			frame->tf_r0 = td->td_retval[0];
			frame->tf_r1 = td->td_retval[1];
		}
		frame->tf_spsr &= ~PSR_C;   /* carry bit */
		break;
	case ERESTART:
		/*
		 * Reconstruct the pc to point at the swi.
		 */
#if __ARM_ARCH >= 7
		if ((frame->tf_spsr & PSR_T) != 0)
			frame->tf_pc -= THUMB_INSN_SIZE;
		else
#endif
			frame->tf_pc -= INSN_SIZE;
		break;
	case EJUSTRETURN:
		/* nothing to do */
		break;
	default:
		frame->tf_r0 = SV_ABI_ERRNO(td->td_proc, error);
		frame->tf_spsr |= PSR_C;    /* carry bit */
		break;
	}
}