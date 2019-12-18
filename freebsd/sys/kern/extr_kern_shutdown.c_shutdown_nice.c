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
 int RB_NOSYNC ; 
 int /*<<< orphan*/  SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/ * initproc ; 
 int /*<<< orphan*/  kern_reboot (int) ; 
 TYPE_1__ shutdown_nice_task ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_fast ; 

void
shutdown_nice(int howto)
{

	if (initproc != NULL && !SCHEDULER_STOPPED()) {
		shutdown_nice_task.ta_context = (void *)(uintptr_t)howto;
		taskqueue_enqueue(taskqueue_fast, &shutdown_nice_task);
	} else {
		/*
		 * No init(8) running, or scheduler would not allow it
		 * to run, so simply reboot.
		 */
		kern_reboot(howto | RB_NOSYNC);
	}
}