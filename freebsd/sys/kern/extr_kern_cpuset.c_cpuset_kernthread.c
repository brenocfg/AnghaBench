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
struct thread {struct cpuset* td_cpuset; } ;
struct cpuset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuset_kernel ; 
 struct cpuset* cpuset_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
cpuset_kernthread(struct thread *td)
{
	struct cpuset *set;

	thread_lock(td);
	set = td->td_cpuset;
	td->td_cpuset = cpuset_ref(cpuset_kernel);
	thread_unlock(td);
	cpuset_rel(set);
}