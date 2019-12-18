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
struct umtx_q {struct umtx_pi* uq_pi_blocked; } ;
struct umtx_pi {struct thread* pi_owner; } ;
struct thread {int td_lend_user_pri; struct umtx_q* td_umtxq; TYPE_1__* td_proc; } ;
struct TYPE_2__ {scalar_t__ p_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ P_MAGIC ; 
 int UPRI (struct thread*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_lend_user_prio (struct thread*,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  umtx_lock ; 
 int /*<<< orphan*/  umtx_pi_adjust_thread (struct umtx_pi*,struct thread*) ; 
 scalar_t__ umtx_pi_check_loop (struct umtx_pi*) ; 

__attribute__((used)) static void
umtx_propagate_priority(struct thread *td)
{
	struct umtx_q *uq;
	struct umtx_pi *pi;
	int pri;

	mtx_assert(&umtx_lock, MA_OWNED);
	pri = UPRI(td);
	uq = td->td_umtxq;
	pi = uq->uq_pi_blocked;
	if (pi == NULL)
		return;
	if (umtx_pi_check_loop(pi))
		return;

	for (;;) {
		td = pi->pi_owner;
		if (td == NULL || td == curthread)
			return;

		MPASS(td->td_proc != NULL);
		MPASS(td->td_proc->p_magic == P_MAGIC);

		thread_lock(td);
		if (td->td_lend_user_pri > pri)
			sched_lend_user_prio(td, pri);
		else {
			thread_unlock(td);
			break;
		}
		thread_unlock(td);

		/*
		 * Pick up the lock that td is blocked on.
		 */
		uq = td->td_umtxq;
		pi = uq->uq_pi_blocked;
		if (pi == NULL)
			break;
		/* Resort td on the list if needed. */
		umtx_pi_adjust_thread(pi, td);
	}
}