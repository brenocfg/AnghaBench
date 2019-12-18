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
struct work_struct {int /*<<< orphan*/  work_task; TYPE_1__* work_queue; int /*<<< orphan*/  state; } ;
struct taskqueue {int dummy; } ;
struct TYPE_2__ {struct taskqueue* taskqueue; } ;

/* Variables and functions */
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
#define  WORK_ST_IDLE 128 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (struct taskqueue*,int /*<<< orphan*/ *) ; 
 int taskqueue_poll_is_busy (struct taskqueue*,int /*<<< orphan*/ *) ; 

bool
linux_flush_work(struct work_struct *work)
{
	struct taskqueue *tq;
	bool retval;

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "linux_flush_work() might sleep");

	switch (atomic_read(&work->state)) {
	case WORK_ST_IDLE:
		return (false);
	default:
		tq = work->work_queue->taskqueue;
		retval = taskqueue_poll_is_busy(tq, &work->work_task);
		taskqueue_drain(tq, &work->work_task);
		return (retval);
	}
}