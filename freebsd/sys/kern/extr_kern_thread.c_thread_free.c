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
struct thread {scalar_t__ td_kstack; int /*<<< orphan*/  td_slpcallout; int /*<<< orphan*/ * td_cpuset; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_thread_free (struct thread*) ; 
 int /*<<< orphan*/  cpuset_rel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_profile_thread_exit (struct thread*) ; 
 int /*<<< orphan*/  thread_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vm_thread_dispose (struct thread*) ; 

void
thread_free(struct thread *td)
{

	lock_profile_thread_exit(td);
	if (td->td_cpuset)
		cpuset_rel(td->td_cpuset);
	td->td_cpuset = NULL;
	cpu_thread_free(td);
	if (td->td_kstack != 0)
		vm_thread_dispose(td);
	callout_drain(&td->td_slpcallout);
	uma_zfree(thread_zone, td);
}