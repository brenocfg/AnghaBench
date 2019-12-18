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
typedef  scalar_t__ u_long ;
struct kqueue {int kq_knlistsize; int kq_state; scalar_t__ kq_knhashmask; struct klist* kq_knhash; struct klist* kq_knlist; } ;
struct klist {int dummy; } ;
struct filterops {scalar_t__ f_isfd; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HASH_NOWAIT ; 
 int /*<<< orphan*/  HASH_WAITOK ; 
 int /*<<< orphan*/  KN_HASHSIZE ; 
 scalar_t__ KQEXTENT ; 
 int KQ_CLOSING ; 
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_NOTOWNED (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_UNLOCK (struct kqueue*) ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bcopy (struct klist*,struct klist*,int) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  free (struct klist*,int /*<<< orphan*/ ) ; 
 struct klist* hashinit_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct klist* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kqueue_expand(struct kqueue *kq, struct filterops *fops, uintptr_t ident,
    int mflag)
{
	struct klist *list, *tmp_knhash, *to_free;
	u_long tmp_knhashmask;
	int error, fd, size;

	KQ_NOTOWNED(kq);

	error = 0;
	to_free = NULL;
	if (fops->f_isfd) {
		fd = ident;
		if (kq->kq_knlistsize <= fd) {
			size = kq->kq_knlistsize;
			while (size <= fd)
				size += KQEXTENT;
			list = malloc(size * sizeof(*list), M_KQUEUE, mflag);
			if (list == NULL)
				return ENOMEM;
			KQ_LOCK(kq);
			if ((kq->kq_state & KQ_CLOSING) != 0) {
				to_free = list;
				error = EBADF;
			} else if (kq->kq_knlistsize > fd) {
				to_free = list;
			} else {
				if (kq->kq_knlist != NULL) {
					bcopy(kq->kq_knlist, list,
					    kq->kq_knlistsize * sizeof(*list));
					to_free = kq->kq_knlist;
					kq->kq_knlist = NULL;
				}
				bzero((caddr_t)list +
				    kq->kq_knlistsize * sizeof(*list),
				    (size - kq->kq_knlistsize) * sizeof(*list));
				kq->kq_knlistsize = size;
				kq->kq_knlist = list;
			}
			KQ_UNLOCK(kq);
		}
	} else {
		if (kq->kq_knhashmask == 0) {
			tmp_knhash = hashinit_flags(KN_HASHSIZE, M_KQUEUE,
			    &tmp_knhashmask, (mflag & M_WAITOK) != 0 ?
			    HASH_WAITOK : HASH_NOWAIT);
			if (tmp_knhash == NULL)
				return (ENOMEM);
			KQ_LOCK(kq);
			if ((kq->kq_state & KQ_CLOSING) != 0) {
				to_free = tmp_knhash;
				error = EBADF;
			} else if (kq->kq_knhashmask == 0) {
				kq->kq_knhash = tmp_knhash;
				kq->kq_knhashmask = tmp_knhashmask;
			} else {
				to_free = tmp_knhash;
			}
			KQ_UNLOCK(kq);
		}
	}
	free(to_free, M_KQUEUE);

	KQ_NOTOWNED(kq);
	return (error);
}