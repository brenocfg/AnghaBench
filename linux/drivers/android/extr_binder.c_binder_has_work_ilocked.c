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
struct binder_thread {TYPE_1__* proc; scalar_t__ looper_need_return; scalar_t__ process_todo; } ;
struct TYPE_2__ {int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_worklist_empty_ilocked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool binder_has_work_ilocked(struct binder_thread *thread,
				    bool do_proc_work)
{
	return thread->process_todo ||
		thread->looper_need_return ||
		(do_proc_work &&
		 !binder_worklist_empty_ilocked(&thread->proc->todo));
}