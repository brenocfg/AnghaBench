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
struct rmlock {int /*<<< orphan*/  rm_activeReaders; } ;
struct rm_queue {struct rm_queue* rmq_next; } ;
struct rm_priotracker {scalar_t__ rmp_flags; struct rmlock* rmp_rmlock; } ;
struct pcpu {struct rm_queue pc_rm_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rm_priotracker*,int /*<<< orphan*/ ) ; 
 scalar_t__ RMPF_ONQUEUE ; 
 struct pcpu* get_pcpu () ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_spinlock ; 
 int /*<<< orphan*/  rmp_qentry ; 

__attribute__((used)) static void
rm_cleanIPI(void *arg)
{
	struct pcpu *pc;
	struct rmlock *rm = arg;
	struct rm_priotracker *tracker;
	struct rm_queue *queue;
	pc = get_pcpu();

	for (queue = pc->pc_rm_queue.rmq_next; queue != &pc->pc_rm_queue;
	    queue = queue->rmq_next) {
		tracker = (struct rm_priotracker *)queue;
		if (tracker->rmp_rmlock == rm && tracker->rmp_flags == 0) {
			tracker->rmp_flags = RMPF_ONQUEUE;
			mtx_lock_spin(&rm_spinlock);
			LIST_INSERT_HEAD(&rm->rm_activeReaders, tracker,
			    rmp_qentry);
			mtx_unlock_spin(&rm_spinlock);
		}
	}
}