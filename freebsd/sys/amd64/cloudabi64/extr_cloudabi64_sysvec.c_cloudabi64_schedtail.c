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
struct trapframe {int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rax; } ;
struct thread {int /*<<< orphan*/  td_tid; struct trapframe* td_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOUDABI_PROCESS_CHILD ; 

__attribute__((used)) static void
cloudabi64_schedtail(struct thread *td)
{
	struct trapframe *frame = td->td_frame;

	/* Initial register values for processes returning from fork. */
	frame->tf_rax = CLOUDABI_PROCESS_CHILD;
	frame->tf_rdx = td->td_tid;
}