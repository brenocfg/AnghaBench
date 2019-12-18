#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct kqueue {int /*<<< orphan*/  kq_knhashmask; struct klist* kq_knhash; struct klist* kq_knlist; } ;
struct TYPE_3__ {int /*<<< orphan*/  filter; } ;
struct knote {int kn_status; int kn_influx; size_t kn_id; TYPE_2__* kn_fop; TYPE_1__ kn_kevent; int /*<<< orphan*/ * kn_fp; struct kqueue* kn_kq; } ;
struct klist {int dummy; } ;
struct TYPE_4__ {scalar_t__ f_isfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KN_DETACHED ; 
 size_t KN_HASH (size_t,int /*<<< orphan*/ ) ; 
 int KN_QUEUED ; 
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_NOTOWNED (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_UNLOCK_FLUX (struct kqueue*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (struct klist*) ; 
 int /*<<< orphan*/  SLIST_REMOVE (struct klist*,struct knote*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  kn_link ; 
 int /*<<< orphan*/  knote ; 
 int /*<<< orphan*/  knote_dequeue (struct knote*) ; 
 int /*<<< orphan*/  knote_free (struct knote*) ; 
 int /*<<< orphan*/  kqueue_fo_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
knote_drop_detached(struct knote *kn, struct thread *td)
{
	struct kqueue *kq;
	struct klist *list;

	kq = kn->kn_kq;

	KASSERT((kn->kn_status & KN_DETACHED) != 0,
	    ("knote %p still attached", kn));
	KQ_NOTOWNED(kq);

	KQ_LOCK(kq);
	KASSERT(kn->kn_influx == 1,
	    ("knote_drop called on %p with influx %d", kn, kn->kn_influx));

	if (kn->kn_fop->f_isfd)
		list = &kq->kq_knlist[kn->kn_id];
	else
		list = &kq->kq_knhash[KN_HASH(kn->kn_id, kq->kq_knhashmask)];

	if (!SLIST_EMPTY(list))
		SLIST_REMOVE(list, kn, knote, kn_link);
	if (kn->kn_status & KN_QUEUED)
		knote_dequeue(kn);
	KQ_UNLOCK_FLUX(kq);

	if (kn->kn_fop->f_isfd) {
		fdrop(kn->kn_fp, td);
		kn->kn_fp = NULL;
	}
	kqueue_fo_release(kn->kn_kevent.filter);
	kn->kn_fop = NULL;
	knote_free(kn);
}