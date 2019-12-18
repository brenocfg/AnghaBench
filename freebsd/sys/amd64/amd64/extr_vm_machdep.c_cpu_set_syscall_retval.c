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
struct trapframe {int /*<<< orphan*/  tf_rflags; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_err; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rdx; } ;
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_pcb; int /*<<< orphan*/ * td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  SV_ABI_ERRNO (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame;

	frame = td->td_frame;
	if (__predict_true(error == 0)) {
		frame->tf_rax = td->td_retval[0];
		frame->tf_rdx = td->td_retval[1];
		frame->tf_rflags &= ~PSL_C;
		return;
	}

	switch (error) {
	case ERESTART:
		/*
		 * Reconstruct pc, we know that 'syscall' is 2 bytes,
		 * lcall $X,y is 7 bytes, int 0x80 is 2 bytes.
		 * We saved this in tf_err.
		 * %r10 (which was holding the value of %rcx) is restored
		 * for the next iteration.
		 * %r10 restore is only required for freebsd/amd64 processes,
		 * but shall be innocent for any ia32 ABI.
		 *
		 * Require full context restore to get the arguments
		 * in the registers reloaded at return to usermode.
		 */
		frame->tf_rip -= frame->tf_err;
		frame->tf_r10 = frame->tf_rcx;
		set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
		break;

	case EJUSTRETURN:
		break;

	default:
		frame->tf_rax = SV_ABI_ERRNO(td->td_proc, error);
		frame->tf_rflags |= PSL_C;
		break;
	}
}