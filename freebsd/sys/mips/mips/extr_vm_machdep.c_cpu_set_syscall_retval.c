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
struct trapframe {unsigned int v0; unsigned int a0; unsigned int a1; unsigned int v1; int a3; int /*<<< orphan*/  pc; } ;
struct thread {unsigned int* td_retval; TYPE_1__* td_pcb; int /*<<< orphan*/  td_proc; struct trapframe* td_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_tpc; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int SYS___syscall ; 
 unsigned int SYS_lseek ; 
 unsigned int SYS_syscall ; 
 scalar_t__ _QUAD_LOWWORD ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *locr0 = td->td_frame;
	unsigned int code;
	int quad_syscall;

	code = locr0->v0;
	quad_syscall = 0;
#if defined(__mips_n32) || defined(__mips_n64)
#ifdef COMPAT_FREEBSD32
	if (code == SYS___syscall && SV_PROC_FLAG(td->td_proc, SV_ILP32))
		quad_syscall = 1;
#endif
#else
	if (code == SYS___syscall)
		quad_syscall = 1;
#endif

	if (code == SYS_syscall)
		code = locr0->a0;
	else if (code == SYS___syscall) {
		if (quad_syscall)
			code = _QUAD_LOWWORD ? locr0->a1 : locr0->a0;
		else
			code = locr0->a0;
	}

	switch (error) {
	case 0:
		if (quad_syscall && code != SYS_lseek) {
			/*
			 * System call invoked through the
			 * SYS___syscall interface but the
			 * return value is really just 32
			 * bits.
			 */
			locr0->v0 = td->td_retval[0];
			if (_QUAD_LOWWORD)
				locr0->v1 = td->td_retval[0];
			locr0->a3 = 0;
		} else {
			locr0->v0 = td->td_retval[0];
			locr0->v1 = td->td_retval[1];
			locr0->a3 = 0;
		}
		break;

	case ERESTART:
		locr0->pc = td->td_pcb->pcb_tpc;
		break;

	case EJUSTRETURN:
		break;	/* nothing to do */

	default:
		if (quad_syscall && code != SYS_lseek) {
			locr0->v0 = error;
			if (_QUAD_LOWWORD)
				locr0->v1 = error;
			locr0->a3 = 1;
		} else {
			locr0->v0 = error;
			locr0->a3 = 1;
		}
	}
}