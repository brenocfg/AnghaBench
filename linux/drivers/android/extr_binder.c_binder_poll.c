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
struct poll_table_struct {int dummy; } ;
struct file {struct binder_proc* private_data; } ;
struct binder_thread {int /*<<< orphan*/  wait; int /*<<< orphan*/  proc; int /*<<< orphan*/  looper; } ;
struct binder_proc {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_LOOPER_STATE_POLL ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  POLLERR ; 
 int binder_available_for_proc_work_ilocked (struct binder_thread*) ; 
 struct binder_thread* binder_get_thread (struct binder_proc*) ; 
 scalar_t__ binder_has_work (struct binder_thread*,int) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t binder_poll(struct file *filp,
				struct poll_table_struct *wait)
{
	struct binder_proc *proc = filp->private_data;
	struct binder_thread *thread = NULL;
	bool wait_for_proc_work;

	thread = binder_get_thread(proc);
	if (!thread)
		return POLLERR;

	binder_inner_proc_lock(thread->proc);
	thread->looper |= BINDER_LOOPER_STATE_POLL;
	wait_for_proc_work = binder_available_for_proc_work_ilocked(thread);

	binder_inner_proc_unlock(thread->proc);

	poll_wait(filp, &thread->wait, wait);

	if (binder_has_work(thread, wait_for_proc_work))
		return EPOLLIN;

	return 0;
}