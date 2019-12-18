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
struct trapframe {int /*<<< orphan*/  tf_eflags; int /*<<< orphan*/  tf_eax; int /*<<< orphan*/  tf_err; int /*<<< orphan*/  tf_eip; int /*<<< orphan*/  tf_edx; } ;
struct thread {int /*<<< orphan*/ * td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  cloudabi_convert_errno (int) ; 

__attribute__((used)) static void
cloudabi32_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame = td->td_frame;

	switch (error) {
	case 0:
		/* System call succeeded. */
		frame->tf_eax = td->td_retval[0];
		frame->tf_edx = td->td_retval[1];
		frame->tf_eflags &= ~PSL_C;
		break;
	case ERESTART:
		/* Restart system call. */
		frame->tf_eip -= frame->tf_err;
		break;
	case EJUSTRETURN:
		break;
	default:
		/* System call returned an error. */
		frame->tf_eax = cloudabi_convert_errno(error);
		frame->tf_eflags |= PSL_C;
		break;
	}
}