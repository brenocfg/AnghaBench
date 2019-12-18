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
struct taskqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int taskqueue_drain_tq_active (struct taskqueue*) ; 
 int taskqueue_drain_tq_queue (struct taskqueue*) ; 

void
taskqueue_quiesce(struct taskqueue *queue)
{
	int ret;

	TQ_LOCK(queue);
	do {
		ret = taskqueue_drain_tq_queue(queue);
		if (ret == 0)
			ret = taskqueue_drain_tq_active(queue);
	} while (ret != 0);
	TQ_UNLOCK(queue);
}