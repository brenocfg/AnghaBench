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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  power_pm_fn_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ POWER_PM_TYPE_NONE ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* power_pm_arg ; 
 int /*<<< orphan*/  power_pm_deferred_fn ; 
 int /*<<< orphan*/  power_pm_fn ; 
 int /*<<< orphan*/  power_pm_task ; 
 scalar_t__ power_pm_type ; 

int
power_pm_register(u_int pm_type, power_pm_fn_t pm_fn, void *pm_arg)
{
	int	error;

	if (power_pm_type == POWER_PM_TYPE_NONE ||
	    power_pm_type == pm_type) {
		power_pm_type	= pm_type;
		power_pm_fn	= pm_fn;
		power_pm_arg	= pm_arg;
		error = 0;
		TASK_INIT(&power_pm_task, 0, power_pm_deferred_fn, NULL);
	} else {
		error = ENXIO;
	}

	return (error);
}