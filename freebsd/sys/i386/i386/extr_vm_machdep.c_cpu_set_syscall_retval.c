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
struct thread {TYPE_1__* td_frame; int /*<<< orphan*/  td_proc; int /*<<< orphan*/ * td_retval; } ;
struct TYPE_2__ {int /*<<< orphan*/  tf_eflags; int /*<<< orphan*/  tf_eax; int /*<<< orphan*/  tf_err; int /*<<< orphan*/  tf_eip; int /*<<< orphan*/  tf_edx; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  SV_ABI_ERRNO (int /*<<< orphan*/ ,int) ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{

	switch (error) {
	case 0:
		td->td_frame->tf_eax = td->td_retval[0];
		td->td_frame->tf_edx = td->td_retval[1];
		td->td_frame->tf_eflags &= ~PSL_C;
		break;

	case ERESTART:
		/*
		 * Reconstruct pc, assuming lcall $X,y is 7 bytes, int
		 * 0x80 is 2 bytes. We saved this in tf_err.
		 */
		td->td_frame->tf_eip -= td->td_frame->tf_err;
		break;

	case EJUSTRETURN:
		break;

	default:
		td->td_frame->tf_eax = SV_ABI_ERRNO(td->td_proc, error);
		td->td_frame->tf_eflags |= PSL_C;
		break;
	}
}