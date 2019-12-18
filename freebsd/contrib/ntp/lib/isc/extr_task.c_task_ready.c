#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  scalar_t__ isc_boolean_t ;
struct TYPE_7__ {scalar_t__ mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  work_available; } ;
typedef  TYPE_1__ isc__taskmgr_t ;
struct TYPE_8__ {scalar_t__ state; TYPE_1__* manager; } ;
typedef  TYPE_2__ isc__task_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  SIGNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_MANAGER (TYPE_1__*) ; 
 int /*<<< orphan*/  XTRACE (char*) ; 
 scalar_t__ isc__task_privilege (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_taskmgrmode_normal ; 
 int /*<<< orphan*/  push_readyq (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ task_state_ready ; 

__attribute__((used)) static inline void
task_ready(isc__task_t *task) {
	isc__taskmgr_t *manager = task->manager;
#ifdef USE_WORKER_THREADS
	isc_boolean_t has_privilege = isc__task_privilege((isc_task_t *) task);
#endif /* USE_WORKER_THREADS */

	REQUIRE(VALID_MANAGER(manager));
	REQUIRE(task->state == task_state_ready);

	XTRACE("task_ready");

	LOCK(&manager->lock);
	push_readyq(manager, task);
#ifdef USE_WORKER_THREADS
	if (manager->mode == isc_taskmgrmode_normal || has_privilege)
		SIGNAL(&manager->work_available);
#endif /* USE_WORKER_THREADS */
	UNLOCK(&manager->lock);
}