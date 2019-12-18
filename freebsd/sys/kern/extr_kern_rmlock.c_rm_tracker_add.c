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
struct rm_queue {struct rm_queue* rmq_next; struct rm_queue* rmq_prev; } ;
struct rm_priotracker {struct rm_queue rmp_cpuQueue; } ;
struct pcpu {struct rm_queue pc_rm_queue; } ;

/* Variables and functions */

__attribute__((used)) static void inline
rm_tracker_add(struct pcpu *pc, struct rm_priotracker *tracker)
{
	struct rm_queue *next;

	/* Initialize all tracker pointers */
	tracker->rmp_cpuQueue.rmq_prev = &pc->pc_rm_queue;
	next = pc->pc_rm_queue.rmq_next;
	tracker->rmp_cpuQueue.rmq_next = next;

	/* rmq_prev is not used during froward traversal. */
	next->rmq_prev = &tracker->rmp_cpuQueue;

	/* Update pointer to first element. */
	pc->pc_rm_queue.rmq_next = &tracker->rmp_cpuQueue;
}