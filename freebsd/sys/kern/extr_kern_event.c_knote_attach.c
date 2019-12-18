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
struct kqueue {int kq_state; size_t kq_knlistsize; int /*<<< orphan*/  kq_knhashmask; struct klist* kq_knhash; struct klist* kq_knlist; } ;
struct knote {size_t kn_id; TYPE_1__* kn_fop; } ;
struct klist {int dummy; } ;
struct TYPE_2__ {scalar_t__ f_isfd; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t KN_HASH (size_t,int /*<<< orphan*/ ) ; 
 int KQ_CLOSING ; 
 int /*<<< orphan*/  KQ_OWNED (struct kqueue*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct klist*,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_in_flux (struct knote*) ; 
 int /*<<< orphan*/  kn_link ; 

__attribute__((used)) static int
knote_attach(struct knote *kn, struct kqueue *kq)
{
	struct klist *list;

	KASSERT(kn_in_flux(kn), ("knote %p not marked influx", kn));
	KQ_OWNED(kq);

	if ((kq->kq_state & KQ_CLOSING) != 0)
		return (EBADF);
	if (kn->kn_fop->f_isfd) {
		if (kn->kn_id >= kq->kq_knlistsize)
			return (ENOMEM);
		list = &kq->kq_knlist[kn->kn_id];
	} else {
		if (kq->kq_knhash == NULL)
			return (ENOMEM);
		list = &kq->kq_knhash[KN_HASH(kn->kn_id, kq->kq_knhashmask)];
	}
	SLIST_INSERT_HEAD(list, kn, kn_link);
	return (0);
}