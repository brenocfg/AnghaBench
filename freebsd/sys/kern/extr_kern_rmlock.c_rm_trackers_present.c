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
struct thread {int dummy; } ;
struct rmlock {int dummy; } ;
struct rm_queue {struct rm_queue* rmq_next; } ;
struct rm_priotracker {struct thread const* rmp_thread; struct rmlock const* rmp_rmlock; } ;
struct pcpu {struct rm_queue pc_rm_queue; } ;

/* Variables and functions */

__attribute__((used)) static int
rm_trackers_present(const struct pcpu *pc, const struct rmlock *rm,
    const struct thread *td)
{
	struct rm_queue *queue;
	struct rm_priotracker *tracker;
	int count;

	count = 0;
	for (queue = pc->pc_rm_queue.rmq_next; queue != &pc->pc_rm_queue;
	    queue = queue->rmq_next) {
		tracker = (struct rm_priotracker *)queue;
		if ((tracker->rmp_rmlock == rm) && (tracker->rmp_thread == td))
			count++;
	}
	return (count);
}