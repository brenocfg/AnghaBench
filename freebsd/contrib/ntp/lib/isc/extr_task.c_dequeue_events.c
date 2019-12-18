#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_eventtype_t ;
typedef  int /*<<< orphan*/  isc_eventlist_t ;
struct TYPE_11__ {scalar_t__ ev_type; void* ev_sender; void* ev_tag; } ;
typedef  TYPE_1__ isc_event_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  events; } ;
typedef  TYPE_2__ isc__task_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEQUEUE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENQUEUE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 TYPE_1__* NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PURGE_OK (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_TASK (TYPE_2__*) ; 
 int /*<<< orphan*/  XTRACE (char*) ; 
 int /*<<< orphan*/  ev_link ; 

__attribute__((used)) static unsigned int
dequeue_events(isc__task_t *task, void *sender, isc_eventtype_t first,
	       isc_eventtype_t last, void *tag,
	       isc_eventlist_t *events, isc_boolean_t purging)
{
	isc_event_t *event, *next_event;
	unsigned int count = 0;

	REQUIRE(VALID_TASK(task));
	REQUIRE(last >= first);

	XTRACE("dequeue_events");

	/*
	 * Events matching 'sender', whose type is >= first and <= last, and
	 * whose tag is 'tag' will be dequeued.  If 'purging', matching events
	 * which are marked as unpurgable will not be dequeued.
	 *
	 * sender == NULL means "any sender", and tag == NULL means "any tag".
	 */

	LOCK(&task->lock);

	for (event = HEAD(task->events); event != NULL; event = next_event) {
		next_event = NEXT(event, ev_link);
		if (event->ev_type >= first && event->ev_type <= last &&
		    (sender == NULL || event->ev_sender == sender) &&
		    (tag == NULL || event->ev_tag == tag) &&
		    (!purging || PURGE_OK(event))) {
			DEQUEUE(task->events, event, ev_link);
			ENQUEUE(*events, event, ev_link);
			count++;
		}
	}

	UNLOCK(&task->lock);

	return (count);
}