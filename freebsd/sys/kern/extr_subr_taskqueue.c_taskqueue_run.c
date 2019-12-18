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
 int /*<<< orphan*/  taskqueue_run_locked (struct taskqueue*) ; 

void
taskqueue_run(struct taskqueue *queue)
{

	TQ_LOCK(queue);
	taskqueue_run_locked(queue);
	TQ_UNLOCK(queue);
}