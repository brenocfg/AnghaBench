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
struct binder_thread {int /*<<< orphan*/  proc; } ;

/* Variables and functions */
 int binder_has_work_ilocked (struct binder_thread*,int) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool binder_has_work(struct binder_thread *thread, bool do_proc_work)
{
	bool has_work;

	binder_inner_proc_lock(thread->proc);
	has_work = binder_has_work_ilocked(thread, do_proc_work);
	binder_inner_proc_unlock(thread->proc);

	return has_work;
}