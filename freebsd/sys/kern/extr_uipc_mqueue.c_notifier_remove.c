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
struct proc {int dummy; } ;
struct mqueue_notifier {int /*<<< orphan*/  nt_ksi; } ;
struct mqueue {struct mqueue_notifier* mq_notifier; int /*<<< orphan*/  mq_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifier_delete (struct proc*,struct mqueue_notifier*) ; 
 struct mqueue_notifier* notifier_search (struct proc*,int) ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
notifier_remove(struct proc *p, struct mqueue *mq, int fd)
{
	struct mqueue_notifier *nt;

	mtx_assert(&mq->mq_mutex, MA_OWNED);
	PROC_LOCK(p);
	nt = notifier_search(p, fd);
	if (nt != NULL) {
		if (mq->mq_notifier == nt)
			mq->mq_notifier = NULL;
		sigqueue_take(&nt->nt_ksi);
		notifier_delete(p, nt);
	}
	PROC_UNLOCK(p);
}