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
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_system_long_wq ; 
 int /*<<< orphan*/  linux_system_short_wq ; 
 int /*<<< orphan*/ * system_highpri_wq ; 
 int /*<<< orphan*/ * system_long_wq ; 
 int /*<<< orphan*/ * system_power_efficient_wq ; 
 int /*<<< orphan*/ * system_unbound_wq ; 
 int /*<<< orphan*/ * system_wq ; 

__attribute__((used)) static void
linux_work_uninit(void *arg)
{
	destroy_workqueue(linux_system_short_wq);
	destroy_workqueue(linux_system_long_wq);

	/* clear workqueue pointers */
	system_long_wq = NULL;
	system_wq = NULL;
	system_power_efficient_wq = NULL;
	system_unbound_wq = NULL;
	system_highpri_wq = NULL;
}