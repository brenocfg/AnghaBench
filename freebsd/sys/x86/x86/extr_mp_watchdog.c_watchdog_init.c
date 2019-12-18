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
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  watchdog_callout ; 
 int /*<<< orphan*/  watchdog_change (int) ; 
 int watchdog_cpu ; 

__attribute__((used)) static void
watchdog_init(void *arg)
{

	callout_init(&watchdog_callout, 1);
	if (watchdog_cpu != -1)
		watchdog_change(watchdog_cpu);
}