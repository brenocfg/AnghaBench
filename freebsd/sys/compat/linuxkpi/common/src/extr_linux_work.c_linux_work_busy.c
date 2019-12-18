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
#define  WORK_ST_EXEC 129 
#define  WORK_ST_IDLE 128 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int taskqueue_poll_is_busy (struct taskqueue*,int /*<<< orphan*/ *) ; 

bool
linux_work_busy(struct work_struct *work)
{
	struct taskqueue *tq;

	switch (atomic_read(&work->state)) {
	case WORK_ST_IDLE:
		return (false);
	case WORK_ST_EXEC:
		tq = work->work_queue->taskqueue;
		return (taskqueue_poll_is_busy(tq, &work->work_task));
	default:
		return (true);
	}
}