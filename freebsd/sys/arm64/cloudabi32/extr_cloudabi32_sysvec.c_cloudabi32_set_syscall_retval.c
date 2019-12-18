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
struct trapframe {int tf_elr; int /*<<< orphan*/  tf_spsr; scalar_t__* tf_x; } ;
struct thread {int /*<<< orphan*/  td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
 scalar_t__ CLOUDABI_EFAULT ; 
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int /*<<< orphan*/  PSR_C ; 
 scalar_t__ cloudabi_convert_errno (int) ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
cloudabi32_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame = td->td_frame;

	switch (error) {
	case 0:
		/*
		 * System call succeeded.
		 *
		 * Simply copy out the 64-bit return values into the
		 * same buffer provided for system call arguments. The
		 * vDSO will copy them to the right spot, truncating
		 * pointers and size_t values to 32 bits.
		 */
		if (copyout(td->td_retval, (void *)frame->tf_x[2],
		    sizeof(td->td_retval)) == 0) {
			frame->tf_x[0] = 0;
			frame->tf_spsr &= ~PSR_C;
		} else {
			frame->tf_x[0] = CLOUDABI_EFAULT;
			frame->tf_spsr |= PSR_C;
		}
		break;
	case ERESTART:
		/* Restart system call. */
		frame->tf_elr -= 4;
		break;
	case EJUSTRETURN:
		break;
	default:
		/* System call returned an error. */
		frame->tf_x[0] = cloudabi_convert_errno(error);
		frame->tf_spsr |= PSR_C;
		break;
	}
}