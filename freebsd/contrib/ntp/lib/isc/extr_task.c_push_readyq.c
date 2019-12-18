#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ready_priority_tasks; int /*<<< orphan*/  ready_tasks; } ;
typedef  TYPE_1__ isc__taskmgr_t ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ isc__task_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENQUEUE (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int TASK_F_PRIVILEGED ; 
 int /*<<< orphan*/  ready_link ; 
 int /*<<< orphan*/  ready_priority_link ; 

__attribute__((used)) static inline void
push_readyq(isc__taskmgr_t *manager, isc__task_t *task) {
	ENQUEUE(manager->ready_tasks, task, ready_link);
	if ((task->flags & TASK_F_PRIVILEGED) != 0)
		ENQUEUE(manager->ready_priority_tasks, task,
			ready_priority_link);
}