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
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_ratelimiter_t ;
struct TYPE_3__ {scalar_t__ ev_arg; } ;
typedef  TYPE_1__ isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_ratelimiter_detach (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
ratelimiter_shutdowncomplete(isc_task_t *task, isc_event_t *event) {
	isc_ratelimiter_t *rl = (isc_ratelimiter_t *)event->ev_arg;

	UNUSED(task);

	isc_ratelimiter_detach(&rl);
}