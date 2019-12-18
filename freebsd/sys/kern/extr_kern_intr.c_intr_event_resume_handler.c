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
struct intr_handler {int /*<<< orphan*/  ih_flags; int /*<<< orphan*/  ih_name; struct intr_event* ih_event; } ;
struct intr_event {int /*<<< orphan*/  ie_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IH_SUSP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intr_handler_barrier (struct intr_handler*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
intr_event_resume_handler(void *cookie)
{
	struct intr_handler *handler = (struct intr_handler *)cookie;
	struct intr_event *ie;

	if (handler == NULL)
		return (EINVAL);
	ie = handler->ih_event;
	KASSERT(ie != NULL,
	    ("interrupt handler \"%s\" has a NULL interrupt event",
	    handler->ih_name));

	/*
	 * intr_handler_barrier() acts not only as a barrier,
	 * it also allows to check for any pending interrupts.
	 */
	mtx_lock(&ie->ie_lock);
	handler->ih_flags &= ~IH_SUSP;
	intr_handler_barrier(handler);
	mtx_unlock(&ie->ie_lock);
	return (0);
}