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
typedef  int /*<<< orphan*/  u_char ;
struct umtx_q {struct umtx_pi* uq_pi_blocked; } ;
struct umtx_pi {int dummy; } ;
struct thread {struct umtx_q* td_umtxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_lock ; 
 int /*<<< orphan*/  umtx_pi_adjust_thread (struct umtx_pi*,struct thread*) ; 
 int /*<<< orphan*/  umtx_repropagate_priority (struct umtx_pi*) ; 

void
umtx_pi_adjust(struct thread *td, u_char oldpri)
{
	struct umtx_q *uq;
	struct umtx_pi *pi;

	uq = td->td_umtxq;
	mtx_lock(&umtx_lock);
	/*
	 * Pick up the lock that td is blocked on.
	 */
	pi = uq->uq_pi_blocked;
	if (pi != NULL) {
		umtx_pi_adjust_thread(pi, td);
		umtx_repropagate_priority(pi);
	}
	mtx_unlock(&umtx_lock);
}