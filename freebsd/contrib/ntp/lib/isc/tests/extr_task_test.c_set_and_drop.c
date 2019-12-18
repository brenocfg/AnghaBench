#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
struct TYPE_4__ {scalar_t__ ev_arg; } ;
typedef  TYPE_1__ isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  counter ; 
 int /*<<< orphan*/  isc_event_free (TYPE_1__**) ; 
 scalar_t__ isc_taskmgr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_taskmgr_setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_taskmgrmode_normal ; 
 int /*<<< orphan*/  set_lock ; 
 int /*<<< orphan*/  taskmgr ; 

__attribute__((used)) static void
set_and_drop(isc_task_t *task, isc_event_t *event) {
	int *value = (int *) event->ev_arg;

	UNUSED(task);

	isc_event_free(&event);
	LOCK(&set_lock);
	*value = (int) isc_taskmgr_mode(taskmgr);
	counter++;
	UNLOCK(&set_lock);
	isc_taskmgr_setmode(taskmgr, isc_taskmgrmode_normal);
}