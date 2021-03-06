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
struct auth_xfer {TYPE_1__* task_probe; } ;
struct TYPE_2__ {int /*<<< orphan*/ * env; int /*<<< orphan*/ * worker; int /*<<< orphan*/ * cp; int /*<<< orphan*/ * timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_timer_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfr_probe_disown(struct auth_xfer* xfr)
{
	/* remove timer (from this worker's event base) */
	comm_timer_delete(xfr->task_probe->timer);
	xfr->task_probe->timer = NULL;
	/* remove the commpoint */
	comm_point_delete(xfr->task_probe->cp);
	xfr->task_probe->cp = NULL;
	/* we don't own this item anymore */
	xfr->task_probe->worker = NULL;
	xfr->task_probe->env = NULL;
}