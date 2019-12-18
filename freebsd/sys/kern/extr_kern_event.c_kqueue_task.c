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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct kqueue {int kq_state; TYPE_1__ kq_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KQ_GLOBAL_LOCK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  KQ_GLOBAL_UNLOCK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int KQ_TASKDRAIN ; 
 int KQ_TASKSCHED ; 
 int /*<<< orphan*/  KQ_UNLOCK (struct kqueue*) ; 
 int /*<<< orphan*/  kq_global ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
kqueue_task(void *arg, int pending)
{
	struct kqueue *kq;
	int haskqglobal;

	haskqglobal = 0;
	kq = arg;

	KQ_GLOBAL_LOCK(&kq_global, haskqglobal);
	KQ_LOCK(kq);

	KNOTE_LOCKED(&kq->kq_sel.si_note, 0);

	kq->kq_state &= ~KQ_TASKSCHED;
	if ((kq->kq_state & KQ_TASKDRAIN) == KQ_TASKDRAIN) {
		wakeup(&kq->kq_state);
	}
	KQ_UNLOCK(kq);
	KQ_GLOBAL_UNLOCK(&kq_global, haskqglobal);
}