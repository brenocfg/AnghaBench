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
struct trapframe {int tf_elr; int /*<<< orphan*/ * tf_x; int /*<<< orphan*/  tf_spsr; } ;
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/ * td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  PSR_C ; 
 int /*<<< orphan*/  SV_ABI_ERRNO (int /*<<< orphan*/ ,int) ; 

void
cpu_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame;

	frame = td->td_frame;

	switch (error) {
	case 0:
		frame->tf_x[0] = td->td_retval[0];
		frame->tf_x[1] = td->td_retval[1];
		frame->tf_spsr &= ~PSR_C;	/* carry bit */
		break;
	case ERESTART:
		frame->tf_elr -= 4;
		break;
	case EJUSTRETURN:
		break;
	default:
		frame->tf_spsr |= PSR_C;	/* carry bit */
		frame->tf_x[0] = SV_ABI_ERRNO(td->td_proc, error);
		break;
	}
}