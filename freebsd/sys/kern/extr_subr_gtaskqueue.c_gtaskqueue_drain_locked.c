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
struct gtaskqueue {int dummy; } ;
struct gtask {int ta_flags; } ;

/* Variables and functions */
 int TASK_ENQUEUED ; 
 int /*<<< orphan*/  TQ_SLEEP (struct gtaskqueue*,struct gtask*,char*) ; 
 scalar_t__ task_is_running (struct gtaskqueue*,struct gtask*) ; 

__attribute__((used)) static void
gtaskqueue_drain_locked(struct gtaskqueue *queue, struct gtask *gtask)
{
	while ((gtask->ta_flags & TASK_ENQUEUED) || task_is_running(queue, gtask))
		TQ_SLEEP(queue, gtask, "gtq_drain");
}