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
 void* alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int linux_default_wq_cpus ; 
 void* linux_system_long_wq ; 
 void* linux_system_short_wq ; 
 int mp_ncpus ; 
 void* system_highpri_wq ; 
 void* system_long_wq ; 
 void* system_power_efficient_wq ; 
 void* system_unbound_wq ; 
 void* system_wq ; 

__attribute__((used)) static void
linux_work_init(void *arg)
{
	int max_wq_cpus = mp_ncpus + 1;

	/* avoid deadlock when there are too few threads */
	if (max_wq_cpus < 4)
		max_wq_cpus = 4;

	/* set default number of CPUs */
	linux_default_wq_cpus = max_wq_cpus;

	linux_system_short_wq = alloc_workqueue("linuxkpi_short_wq", 0, max_wq_cpus);
	linux_system_long_wq = alloc_workqueue("linuxkpi_long_wq", 0, max_wq_cpus);

	/* populate the workqueue pointers */
	system_long_wq = linux_system_long_wq;
	system_wq = linux_system_short_wq;
	system_power_efficient_wq = linux_system_short_wq;
	system_unbound_wq = linux_system_short_wq;
	system_highpri_wq = linux_system_short_wq;
}