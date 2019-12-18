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
struct prison {int pr_uref; int /*<<< orphan*/  pr_mtx; int /*<<< orphan*/  pr_task; int /*<<< orphan*/  pr_ref; int /*<<< orphan*/  pr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void
prison_proc_free(struct prison *pr)
{

	mtx_lock(&pr->pr_mtx);
	KASSERT(pr->pr_uref > 0,
	    ("Trying to kill a process in a dead prison (jid=%d)", pr->pr_id));
	if (pr->pr_uref > 1)
		pr->pr_uref--;
	else {
		/*
		 * Don't remove the last user reference in this context, which
		 * is expected to be a process that is not only locked, but
		 * also half dead.
		 */
		pr->pr_ref++;
		mtx_unlock(&pr->pr_mtx);
		taskqueue_enqueue(taskqueue_thread, &pr->pr_task);
		return;
	}
	mtx_unlock(&pr->pr_mtx);
}