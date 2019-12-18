#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ta_context; } ;

/* Variables and functions */
 int POWER_SLEEP_STATE_HIBERNATE ; 
 int POWER_SLEEP_STATE_STANDBY ; 
 int POWER_SLEEP_STATE_SUSPEND ; 
 int /*<<< orphan*/ * power_pm_fn ; 
 TYPE_1__ power_pm_task ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void
power_pm_suspend(int state)
{
	if (power_pm_fn == NULL)
		return;

	if (state != POWER_SLEEP_STATE_STANDBY &&
	    state != POWER_SLEEP_STATE_SUSPEND &&
	    state != POWER_SLEEP_STATE_HIBERNATE)
		return;
	power_pm_task.ta_context = (void *)(intptr_t)state;
	taskqueue_enqueue(taskqueue_thread, &power_pm_task);
}