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
struct trapframe {int /*<<< orphan*/ * tf_x; } ;
struct thread {int td_pflags; int /*<<< orphan*/  td_tid; struct trapframe* td_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOUDABI_PROCESS_CHILD ; 
 int TDP_FORKING ; 

__attribute__((used)) static void
cloudabi64_schedtail(struct thread *td)
{
	struct trapframe *frame = td->td_frame;

	/*
	 * Initial register values for processes returning from fork.
	 * Make sure that we only set these values when forking, not
	 * when creating a new thread.
	 */
	if ((td->td_pflags & TDP_FORKING) != 0) {
		frame->tf_x[0] = CLOUDABI_PROCESS_CHILD;
		frame->tf_x[1] = td->td_tid;
	}
}