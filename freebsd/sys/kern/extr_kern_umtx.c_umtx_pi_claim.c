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
struct umtx_q {struct thread* uq_thread; } ;
struct umtx_pi {int /*<<< orphan*/  pi_blocked; struct thread* pi_owner; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 struct umtx_q* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int UPRI (struct thread*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_lend_user_prio (struct thread*,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  umtx_lock ; 
 int /*<<< orphan*/  umtx_pi_setowner (struct umtx_pi*,struct thread*) ; 

__attribute__((used)) static int
umtx_pi_claim(struct umtx_pi *pi, struct thread *owner)
{
	struct umtx_q *uq;
	int pri;

	mtx_lock(&umtx_lock);
	if (pi->pi_owner == owner) {
		mtx_unlock(&umtx_lock);
		return (0);
	}

	if (pi->pi_owner != NULL) {
		/*
		 * userland may have already messed the mutex, sigh.
		 */
		mtx_unlock(&umtx_lock);
		return (EPERM);
	}
	umtx_pi_setowner(pi, owner);
	uq = TAILQ_FIRST(&pi->pi_blocked);
	if (uq != NULL) {
		pri = UPRI(uq->uq_thread);
		thread_lock(owner);
		if (pri < UPRI(owner))
			sched_lend_user_prio(owner, pri);
		thread_unlock(owner);
	}
	mtx_unlock(&umtx_lock);
	return (0);
}