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
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

void
smp_rendezvous_cpus(cpuset_t map,
	void (*setup_func)(void *), 
	void (*action_func)(void *),
	void (*teardown_func)(void *),
	void *arg)
{
	/*
	 * In the !SMP case we just need to ensure the same initial conditions
	 * as the SMP case.
	 */
	spinlock_enter();
	if (setup_func != NULL)
		setup_func(arg);
	if (action_func != NULL)
		action_func(arg);
	if (teardown_func != NULL)
		teardown_func(arg);
	spinlock_exit();
}