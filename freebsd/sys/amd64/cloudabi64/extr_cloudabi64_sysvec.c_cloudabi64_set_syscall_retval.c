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
struct thread {int /*<<< orphan*/  td_pcb; int /*<<< orphan*/ * td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  cloudabi_convert_errno (int) ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cloudabi64_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame = td->td_frame;

	switch (error) {
	case 0:
		/* System call succeeded. */
		frame->tf_rax = td->td_retval[0];
		frame->tf_rdx = td->td_retval[1];
		frame->tf_rflags &= ~PSL_C;
		break;
	case ERESTART:
		/* Restart system call. */
		frame->tf_rip -= frame->tf_err;
		frame->tf_r10 = frame->tf_rcx;
		set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
		break;
	case EJUSTRETURN:
		break;
	default:
		/* System call returned an error. */
		frame->tf_rax = cloudabi_convert_errno(error);
		frame->tf_rflags |= PSL_C;
		break;
	}
}