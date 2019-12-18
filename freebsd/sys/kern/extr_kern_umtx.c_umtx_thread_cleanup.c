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
struct umtx_q {scalar_t__ uq_inherited_pri; int /*<<< orphan*/  uq_pi_contested; } ;
struct umtx_pi {int /*<<< orphan*/ * pi_owner; } ;
struct thread {uintptr_t td_rb_inact; scalar_t__ td_rb_list; scalar_t__ td_rbp_list; struct umtx_q* td_umtxq; } ;

/* Variables and functions */
 scalar_t__ PRI_MAX ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct umtx_pi* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct umtx_pi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi_link ; 
 int /*<<< orphan*/  sched_lend_user_prio_cond (struct thread*,scalar_t__) ; 
 int /*<<< orphan*/  umtx_cleanup_rb_list (struct thread*,scalar_t__,uintptr_t*,char*) ; 
 int /*<<< orphan*/  umtx_handle_rb (struct thread*,uintptr_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  umtx_lock ; 
 int /*<<< orphan*/  umtx_read_uptr (struct thread*,uintptr_t,uintptr_t*) ; 

__attribute__((used)) static void
umtx_thread_cleanup(struct thread *td)
{
	struct umtx_q *uq;
	struct umtx_pi *pi;
	uintptr_t rb_inact;

	/*
	 * Disown pi mutexes.
	 */
	uq = td->td_umtxq;
	if (uq != NULL) {
		if (uq->uq_inherited_pri != PRI_MAX ||
		    !TAILQ_EMPTY(&uq->uq_pi_contested)) {
			mtx_lock(&umtx_lock);
			uq->uq_inherited_pri = PRI_MAX;
			while ((pi = TAILQ_FIRST(&uq->uq_pi_contested)) != NULL) {
				pi->pi_owner = NULL;
				TAILQ_REMOVE(&uq->uq_pi_contested, pi, pi_link);
			}
			mtx_unlock(&umtx_lock);
		}
		sched_lend_user_prio_cond(td, PRI_MAX);
	}

	if (td->td_rb_inact == 0 && td->td_rb_list == 0 && td->td_rbp_list == 0)
		return;

	/*
	 * Handle terminated robust mutexes.  Must be done after
	 * robust pi disown, otherwise unlock could see unowned
	 * entries.
	 */
	rb_inact = td->td_rb_inact;
	if (rb_inact != 0)
		(void)umtx_read_uptr(td, rb_inact, &rb_inact);
	umtx_cleanup_rb_list(td, td->td_rb_list, &rb_inact, "");
	umtx_cleanup_rb_list(td, td->td_rbp_list, &rb_inact, "priv ");
	if (rb_inact != 0)
		(void)umtx_handle_rb(td, rb_inact, NULL, true);
}