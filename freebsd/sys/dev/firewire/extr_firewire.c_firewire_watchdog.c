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
struct firewire_comm {int /*<<< orphan*/  timeout_callout; int /*<<< orphan*/  task_timeout; int /*<<< orphan*/  taskqueue; } ;

/* Variables and functions */
 int WATCHDOG_HZ ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct firewire_comm*) ; 
 int hz ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
firewire_watchdog(void *arg)
{
	struct firewire_comm *fc;
	static int watchdog_clock = 0;

	fc = arg;

	/*
	 * At boot stage, the device interrupt is disabled and
	 * We encounter a timeout easily. To avoid this,
	 * ignore clock interrupt for a while.
	 */
	if (watchdog_clock > WATCHDOG_HZ * 15)
		taskqueue_enqueue(fc->taskqueue, &fc->task_timeout);
	else
		watchdog_clock++;

	callout_reset(&fc->timeout_callout, hz / WATCHDOG_HZ,
	    firewire_watchdog, fc);
}