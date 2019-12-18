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
struct binder_thread {int looper; int /*<<< orphan*/  todo; int /*<<< orphan*/  transaction_stack; } ;

/* Variables and functions */
 int BINDER_LOOPER_STATE_ENTERED ; 
 int BINDER_LOOPER_STATE_REGISTERED ; 
 scalar_t__ binder_worklist_empty_ilocked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool binder_available_for_proc_work_ilocked(struct binder_thread *thread)
{
	return !thread->transaction_stack &&
		binder_worklist_empty_ilocked(&thread->todo) &&
		(thread->looper & (BINDER_LOOPER_STATE_ENTERED |
				   BINDER_LOOPER_STATE_REGISTERED));
}