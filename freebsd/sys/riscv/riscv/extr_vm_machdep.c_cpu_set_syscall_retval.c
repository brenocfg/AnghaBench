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
struct trapframe {int* tf_a; int* tf_t; int tf_sepc; } ;
struct thread {int* td_retval; struct trapframe* td_frame; } ;

/* Variables and functions */
#define  EJUSTRETURN 129 
#define  ERESTART 128 

void
cpu_set_syscall_retval(struct thread *td, int error)
{
	struct trapframe *frame;

	frame = td->td_frame;

	switch (error) {
	case 0:
		frame->tf_a[0] = td->td_retval[0];
		frame->tf_a[1] = td->td_retval[1];
		frame->tf_t[0] = 0;		/* syscall succeeded */
		break;
	case ERESTART:
		frame->tf_sepc -= 4;		/* prev instruction */
		break;
	case EJUSTRETURN:
		break;
	default:
		frame->tf_a[0] = error;
		frame->tf_t[0] = 1;		/* syscall error */
		break;
	}
}