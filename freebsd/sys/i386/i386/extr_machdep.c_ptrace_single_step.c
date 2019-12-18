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
struct thread {int /*<<< orphan*/  td_dbgflags; TYPE_1__* td_frame; int /*<<< orphan*/  td_proc; } ;
struct TYPE_2__ {int tf_eflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PSL_T ; 
 int /*<<< orphan*/  TDB_STEP ; 

int
ptrace_single_step(struct thread *td)
{

	PROC_LOCK_ASSERT(td->td_proc, MA_OWNED);
	if ((td->td_frame->tf_eflags & PSL_T) == 0) {
		td->td_frame->tf_eflags |= PSL_T;
		td->td_dbgflags |= TDB_STEP;
	}
	return (0);
}