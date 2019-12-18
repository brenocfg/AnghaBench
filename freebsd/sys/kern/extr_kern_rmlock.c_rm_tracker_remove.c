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
struct rm_queue {struct rm_queue* rmq_next; struct rm_queue* rmq_prev; } ;
struct TYPE_2__ {struct rm_queue* rmq_prev; struct rm_queue* rmq_next; } ;
struct rm_priotracker {TYPE_1__ rmp_cpuQueue; } ;
struct pcpu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void inline
rm_tracker_remove(struct pcpu *pc, struct rm_priotracker *tracker)
{
	struct rm_queue *next, *prev;

	next = tracker->rmp_cpuQueue.rmq_next;
	prev = tracker->rmp_cpuQueue.rmq_prev;

	/* Not used during forward traversal. */
	next->rmq_prev = prev;

	/* Remove from list. */
	prev->rmq_next = next;
}