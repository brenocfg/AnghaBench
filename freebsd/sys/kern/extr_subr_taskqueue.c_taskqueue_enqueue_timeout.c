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
struct timeout_task {int dummy; } ;
struct taskqueue {int dummy; } ;

/* Variables and functions */
 int taskqueue_enqueue_timeout_sbt (struct taskqueue*,struct timeout_task*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tick_sbt ; 

int
taskqueue_enqueue_timeout(struct taskqueue *queue,
    struct timeout_task *ttask, int ticks)
{

	return (taskqueue_enqueue_timeout_sbt(queue, ttask, ticks * tick_sbt,
	    0, 0));
}