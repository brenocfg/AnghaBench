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
struct thread {TYPE_2__* td_proc; } ;
struct TYPE_4__ {TYPE_1__* p_sigacts; } ;
struct TYPE_3__ {int /*<<< orphan*/  ps_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SIGPENDING (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int issignal (struct thread*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
cursig(struct thread *td)
{
	PROC_LOCK_ASSERT(td->td_proc, MA_OWNED);
	mtx_assert(&td->td_proc->p_sigacts->ps_mtx, MA_OWNED);
	THREAD_LOCK_ASSERT(td, MA_NOTOWNED);
	return (SIGPENDING(td) ? issignal(td) : 0);
}