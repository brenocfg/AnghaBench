#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct trapframe {int /*<<< orphan*/  tf_elr; int /*<<< orphan*/ * tf_x; } ;
struct thread {int /*<<< orphan*/  td_tid; struct trapframe* td_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry_point; scalar_t__ stack_len; scalar_t__ stack; int /*<<< orphan*/  argument; } ;
typedef  TYPE_1__ cloudabi32_threadattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STACKALIGN (scalar_t__) ; 
 int /*<<< orphan*/  TO_PTR (int /*<<< orphan*/ ) ; 
 int cpu_set_user_tls (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct trapframe*,int /*<<< orphan*/ ,int) ; 

int
cloudabi32_thread_setregs(struct thread *td,
    const cloudabi32_threadattr_t *attr, uint32_t tcb)
{
	struct trapframe *frame;

	/*
	 * Pass in the thread ID of the new thread and the argument
	 * pointer provided by the parent thread in as arguments to the
	 * entry point.
	 */
	frame = td->td_frame;
	memset(frame, 0, sizeof(*frame));
	frame->tf_x[0] = td->td_tid;
	frame->tf_x[1] = attr->argument;
	frame->tf_x[13] = STACKALIGN(attr->stack + attr->stack_len);
	frame->tf_elr = attr->entry_point;

	/* Set up TLS. */
	return (cpu_set_user_tls(td, TO_PTR(tcb)));
}