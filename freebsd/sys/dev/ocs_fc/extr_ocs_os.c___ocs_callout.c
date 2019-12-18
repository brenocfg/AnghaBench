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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  callout; } ;
typedef  TYPE_1__ ocs_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
__ocs_callout(void *t)
{
	ocs_timer_t *timer = t;

	if (callout_pending(&timer->callout)) {
		/* Callout was reset */
		return;
	}

	if (!callout_active(&timer->callout)) {
		/* Callout was stopped */
		return;
	}

	callout_deactivate(&timer->callout);

	if (timer->func) {
		timer->func(timer->data);
	}
}