#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_3__ {scalar_t__ references; scalar_t__ state; int /*<<< orphan*/  events; } ;
typedef  TYPE_1__ isc__task_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  XTRACE (char*) ; 
 scalar_t__ task_state_idle ; 
 scalar_t__ task_state_ready ; 

__attribute__((used)) static inline isc_boolean_t
task_detach(isc__task_t *task) {

	/*
	 * Caller must be holding the task lock.
	 */

	REQUIRE(task->references > 0);

	XTRACE("detach");

	task->references--;
	if (task->references == 0 && task->state == task_state_idle) {
		INSIST(EMPTY(task->events));
		/*
		 * There are no references to this task, and no
		 * pending events.  We could try to optimize and
		 * either initiate shutdown or clean up the task,
		 * depending on its state, but it's easier to just
		 * make the task ready and allow run() or the event
		 * loop to deal with shutting down and termination.
		 */
		task->state = task_state_ready;
		return (ISC_TRUE);
	}

	return (ISC_FALSE);
}