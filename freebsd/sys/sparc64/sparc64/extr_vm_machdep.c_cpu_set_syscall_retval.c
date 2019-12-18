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
struct thread {TYPE_2__* td_frame; int /*<<< orphan*/  td_proc; TYPE_1__* td_pcb; int /*<<< orphan*/ * td_retval; } ;
struct TYPE_4__ {int tf_tnpc; int /*<<< orphan*/  tf_tstate; int /*<<< orphan*/ * tf_out; int /*<<< orphan*/  tf_tpc; } ;
struct TYPE_3__ {int /*<<< orphan*/  pcb_tpc; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  SV_ABI_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TSTATE_XCC_C ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{

	switch (error) {
	case 0:
		td->td_frame->tf_out[0] = td->td_retval[0];
		td->td_frame->tf_out[1] = td->td_retval[1];
		td->td_frame->tf_tstate &= ~TSTATE_XCC_C;
		break;

	case ERESTART:
		/*
		 * Undo the tpc advancement we have done on syscall
		 * enter, we want to reexecute the system call.
		 */
		td->td_frame->tf_tpc = td->td_pcb->pcb_tpc;
		td->td_frame->tf_tnpc -= 4;
		break;

	case EJUSTRETURN:
		break;

	default:
		td->td_frame->tf_out[0] = SV_ABI_ERRNO(td->td_proc, error);
		td->td_frame->tf_tstate |= TSTATE_XCC_C;
		break;
	}
}