#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  callout; } ;
struct delayed_work {int /*<<< orphan*/  work; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_work_fn (int /*<<< orphan*/ *,int) ; 

void
linux_delayed_work_fn(void *context, int pending)
{
	struct delayed_work *dwork = context;

	/*
	 * Make sure the timer belonging to the delayed work gets
	 * drained before invoking the work function. Else the timer
	 * mutex may still be in use which can lead to use-after-free
	 * situations, because the work function might free the work
	 * structure before returning.
	 */
	callout_drain(&dwork->timer.callout);

	linux_work_fn(&dwork->work, pending);
}