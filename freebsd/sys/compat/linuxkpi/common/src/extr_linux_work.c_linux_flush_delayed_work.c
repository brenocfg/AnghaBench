#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct taskqueue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  work_task; TYPE_1__* work_queue; int /*<<< orphan*/  state; } ;
struct delayed_work {TYPE_2__ work; } ;
struct TYPE_3__ {struct taskqueue* taskqueue; } ;

/* Variables and functions */
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
#define  WORK_ST_IDLE 129 
#define  WORK_ST_TIMER 128 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_cancel_timer (struct delayed_work*,int) ; 
 int /*<<< orphan*/  linux_delayed_work_enqueue (struct delayed_work*) ; 
 int /*<<< orphan*/  taskqueue_drain (struct taskqueue*,int /*<<< orphan*/ *) ; 
 int taskqueue_poll_is_busy (struct taskqueue*,int /*<<< orphan*/ *) ; 

bool
linux_flush_delayed_work(struct delayed_work *dwork)
{
	struct taskqueue *tq;
	bool retval;

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "linux_flush_delayed_work() might sleep");

	switch (atomic_read(&dwork->work.state)) {
	case WORK_ST_IDLE:
		return (false);
	case WORK_ST_TIMER:
		if (linux_cancel_timer(dwork, 1))
			linux_delayed_work_enqueue(dwork);
		/* FALLTHROUGH */
	default:
		tq = dwork->work.work_queue->taskqueue;
		retval = taskqueue_poll_is_busy(tq, &dwork->work.work_task);
		taskqueue_drain(tq, &dwork->work.work_task);
		return (retval);
	}
}