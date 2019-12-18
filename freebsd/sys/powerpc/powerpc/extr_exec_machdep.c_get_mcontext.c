#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_frame; } ;
struct TYPE_7__ {int /*<<< orphan*/  mc_onstack; } ;
typedef  TYPE_2__ mcontext_t ;
struct TYPE_8__ {int /*<<< orphan*/  td_proc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fixreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 TYPE_5__* curthread ; 
 int grab_mcontext (struct thread*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sigonstack (int /*<<< orphan*/ ) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int flags)
{
	int error;

	error = grab_mcontext(td, mcp, flags);
	if (error == 0) {
		PROC_LOCK(curthread->td_proc);
		mcp->mc_onstack = sigonstack(td->td_frame->fixreg[1]);
		PROC_UNLOCK(curthread->td_proc);
	}

	return (error);
}