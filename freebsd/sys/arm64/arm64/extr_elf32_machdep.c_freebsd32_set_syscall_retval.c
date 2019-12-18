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
struct trapframe {int* tf_x; int tf_spsr; int tf_elr; } ;
struct thread {int* td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 
 int PSR_C ; 
 int PSR_T ; 

__attribute__((used)) static void
freebsd32_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame;

	frame = td->td_frame;
	switch (error) {
	case 0:
		frame->tf_x[0] = td->td_retval[0];
		frame->tf_x[1] = td->td_retval[1];
		frame->tf_spsr &= ~PSR_C;
		break;
	case ERESTART:
		/*
		 * Reconstruct the pc to point at the swi.
		 */
		if ((frame->tf_spsr & PSR_T) != 0)
			frame->tf_elr -= 2; //THUMB_INSN_SIZE;
		else
			frame->tf_elr -= 4; //INSN_SIZE;
		break;
	case EJUSTRETURN:
		/* nothing to do */
		break;
	default:
		frame->tf_x[0] = error;
		frame->tf_spsr |= PSR_C;
		break;
	}
}