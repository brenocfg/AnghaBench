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
typedef  int /*<<< orphan*/  u_int ;
struct taskqueue {int dummy; } ;
struct task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int taskqueue_cancel_locked (struct taskqueue*,struct task*,int /*<<< orphan*/ *) ; 

int
taskqueue_cancel(struct taskqueue *queue, struct task *task, u_int *pendp)
{
	int error;

	TQ_LOCK(queue);
	error = taskqueue_cancel_locked(queue, task, pendp);
	TQ_UNLOCK(queue);

	return (error);
}