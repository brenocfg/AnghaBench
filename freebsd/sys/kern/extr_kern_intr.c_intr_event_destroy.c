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
struct intr_event {int /*<<< orphan*/  ie_lock; int /*<<< orphan*/ * ie_thread; int /*<<< orphan*/  ie_handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int /*<<< orphan*/  M_ITHREAD ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct intr_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_list ; 
 int /*<<< orphan*/  event_lock ; 
 int /*<<< orphan*/  free (struct intr_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_list ; 
 int /*<<< orphan*/  ithread_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
intr_event_destroy(struct intr_event *ie)
{

	mtx_lock(&event_lock);
	mtx_lock(&ie->ie_lock);
	if (!CK_SLIST_EMPTY(&ie->ie_handlers)) {
		mtx_unlock(&ie->ie_lock);
		mtx_unlock(&event_lock);
		return (EBUSY);
	}
	TAILQ_REMOVE(&event_list, ie, ie_list);
#ifndef notyet
	if (ie->ie_thread != NULL) {
		ithread_destroy(ie->ie_thread);
		ie->ie_thread = NULL;
	}
#endif
	mtx_unlock(&ie->ie_lock);
	mtx_unlock(&event_lock);
	mtx_destroy(&ie->ie_lock);
	free(ie, M_ITHREAD);
	return (0);
}