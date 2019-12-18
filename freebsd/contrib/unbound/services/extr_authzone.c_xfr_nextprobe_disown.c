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
struct auth_xfer {TYPE_1__* task_nextprobe; } ;
struct TYPE_2__ {int /*<<< orphan*/ * env; int /*<<< orphan*/ * worker; scalar_t__ next_probe; int /*<<< orphan*/ * timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_timer_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfr_nextprobe_disown(struct auth_xfer* xfr)
{
	/* delete the timer, because the next worker to pick this up may
	 * not have the same event base */
	comm_timer_delete(xfr->task_nextprobe->timer);
	xfr->task_nextprobe->timer = NULL;
	xfr->task_nextprobe->next_probe = 0;
	/* we don't own this item anymore */
	xfr->task_nextprobe->worker = NULL;
	xfr->task_nextprobe->env = NULL;
}