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
struct TYPE_4__ {int /*<<< orphan*/  work_task; TYPE_1__* work_queue; } ;
struct delayed_work {TYPE_2__ work; } ;
struct TYPE_3__ {struct taskqueue* taskqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue (struct taskqueue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_delayed_work_enqueue(struct delayed_work *dwork)
{
	struct taskqueue *tq;

	tq = dwork->work.work_queue->taskqueue;
	taskqueue_enqueue(tq, &dwork->work.work_task);
}