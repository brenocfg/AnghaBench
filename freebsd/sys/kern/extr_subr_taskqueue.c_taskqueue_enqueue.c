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
struct task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int taskqueue_enqueue_locked (struct taskqueue*,struct task*) ; 

int
taskqueue_enqueue(struct taskqueue *queue, struct task *task)
{
	int res;

	TQ_LOCK(queue);
	res = taskqueue_enqueue_locked(queue, task);
	/* The lock is released inside. */

	return (res);
}