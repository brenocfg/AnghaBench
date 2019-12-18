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
struct pmc_owner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  pmclog_schedule_one_cond (struct pmc_owner*) ; 
 int /*<<< orphan*/  sched_bind (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_unbind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmclog_schedule_all(struct pmc_owner *po)
{
	/*
	 * Schedule the current buffer if any and not empty.
	 */
	for (int i = 0; i < mp_ncpus; i++) {
		thread_lock(curthread);
		sched_bind(curthread, i);
		thread_unlock(curthread);
		pmclog_schedule_one_cond(po);
	}
	thread_lock(curthread);
	sched_unbind(curthread);
	thread_unlock(curthread);
}