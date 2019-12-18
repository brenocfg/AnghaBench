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

/* Variables and functions */
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  smp_rendezvous_cpus (int /*<<< orphan*/ ,void (*) (void*),void (*) (void*),void (*) (void*),void*) ; 

void
smp_rendezvous(void (*setup_func)(void *), 
	       void (*action_func)(void *),
	       void (*teardown_func)(void *),
	       void *arg)
{

	smp_rendezvous_cpus(all_cpus, setup_func, action_func, teardown_func,
	    arg);
}