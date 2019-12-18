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
typedef  int /*<<< orphan*/  u_char ;
struct thread {int /*<<< orphan*/  td_name; } ;
struct intr_thread {struct thread* it_thread; struct intr_event* it_event; } ;
struct intr_event {int /*<<< orphan*/  ie_fullname; int /*<<< orphan*/  ie_handlers; int /*<<< orphan*/  ie_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  ih_pri; } ;

/* Variables and functions */
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* CK_SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PRI_MAX_ITHD ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_clear_tdname (struct thread*) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static void
ithread_update(struct intr_thread *ithd)
{
	struct intr_event *ie;
	struct thread *td;
	u_char pri;

	ie = ithd->it_event;
	td = ithd->it_thread;
	mtx_assert(&ie->ie_lock, MA_OWNED);

	/* Determine the overall priority of this event. */
	if (CK_SLIST_EMPTY(&ie->ie_handlers))
		pri = PRI_MAX_ITHD;
	else
		pri = CK_SLIST_FIRST(&ie->ie_handlers)->ih_pri;

	/* Update name and priority. */
	strlcpy(td->td_name, ie->ie_fullname, sizeof(td->td_name));
#ifdef KTR
	sched_clear_tdname(td);
#endif
	thread_lock(td);
	sched_prio(td, pri);
	thread_unlock(td);
}