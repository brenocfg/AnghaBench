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
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;
struct thread {int* td_retval; } ;
struct kqueue {scalar_t__ kq_count; int /*<<< orphan*/  kq_head; int /*<<< orphan*/  kq_lock; int /*<<< orphan*/  kq_state; } ;
struct kevent {int dummy; } ;
struct knote {int kn_status; int kn_flags; scalar_t__ kn_fflags; scalar_t__ kn_data; struct kevent kn_kevent; TYPE_1__* kn_fop; } ;
struct knlist {int dummy; } ;
struct kevent_copyops {int (* k_copyout ) (int /*<<< orphan*/ ,struct kevent*,int) ;int /*<<< orphan*/  arg; } ;
typedef  int sbintime_t ;
struct TYPE_2__ {scalar_t__ (* f_event ) (struct knote*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* f_touch ) (struct knote*,struct kevent*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  f_isfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ABSOLUTE ; 
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  EVENT_PROCESS ; 
 int EV_CLEAR ; 
 int EV_DISPATCH ; 
 int EV_DROP ; 
 int EV_ONESHOT ; 
 int EWOULDBLOCK ; 
 scalar_t__ INT32_MAX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KN_ACTIVE ; 
 int KN_DISABLED ; 
 int KN_KQUEUE ; 
 int KN_MARKER ; 
 int KN_QUEUED ; 
 int KN_SCAN ; 
 int /*<<< orphan*/  KQ_FLUXWAIT ; 
 int /*<<< orphan*/  KQ_FLUX_WAKEUP (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_GLOBAL_LOCK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  KQ_GLOBAL_UNLOCK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  KQ_LOCK (struct kqueue*) ; 
 int KQ_NEVENTS ; 
 int /*<<< orphan*/  KQ_NOTOWNED (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_OWNED (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_SLEEP ; 
 int /*<<< orphan*/  KQ_UNLOCK (struct kqueue*) ; 
 int /*<<< orphan*/  KQ_UNLOCK_FLUX (struct kqueue*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PCATCH ; 
 int PSOCK ; 
 int SBT_MAX ; 
 struct knote* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 scalar_t__ TIMESEL (int*,int) ; 
 int /*<<< orphan*/  kn_enter_flux (struct knote*) ; 
 scalar_t__ kn_in_flux (struct knote*) ; 
 int /*<<< orphan*/  kn_leave_flux (struct knote*) ; 
 struct knlist* kn_list_lock (struct knote*) ; 
 int /*<<< orphan*/  kn_list_unlock (struct knlist*) ; 
 int /*<<< orphan*/  kn_tqe ; 
 struct knote* knote_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knote_drop (struct knote*,struct thread*) ; 
 int /*<<< orphan*/  knote_free (struct knote*) ; 
 int /*<<< orphan*/  kq_global ; 
 int msleep (struct kqueue*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int msleep_sbt (struct kqueue*,int /*<<< orphan*/ *,int,char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct knote*,struct kevent*,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,struct kevent*,int) ; 
 int stub4 (int /*<<< orphan*/ ,struct kevent*,int) ; 
 int tc_precexp ; 
 scalar_t__ tc_tick_sbt ; 
 scalar_t__ timespecisset (struct timespec const*) ; 
 int tstosbt (struct timespec const) ; 

__attribute__((used)) static int
kqueue_scan(struct kqueue *kq, int maxevents, struct kevent_copyops *k_ops,
    const struct timespec *tsp, struct kevent *keva, struct thread *td)
{
	struct kevent *kevp;
	struct knote *kn, *marker;
	struct knlist *knl;
	sbintime_t asbt, rsbt;
	int count, error, haskqglobal, influx, nkev, touch;

	count = maxevents;
	nkev = 0;
	error = 0;
	haskqglobal = 0;

	if (maxevents == 0)
		goto done_nl;

	rsbt = 0;
	if (tsp != NULL) {
		if (tsp->tv_sec < 0 || tsp->tv_nsec < 0 ||
		    tsp->tv_nsec >= 1000000000) {
			error = EINVAL;
			goto done_nl;
		}
		if (timespecisset(tsp)) {
			if (tsp->tv_sec <= INT32_MAX) {
				rsbt = tstosbt(*tsp);
				if (TIMESEL(&asbt, rsbt))
					asbt += tc_tick_sbt;
				if (asbt <= SBT_MAX - rsbt)
					asbt += rsbt;
				else
					asbt = 0;
				rsbt >>= tc_precexp;
			} else
				asbt = 0;
		} else
			asbt = -1;
	} else
		asbt = 0;
	marker = knote_alloc(M_WAITOK);
	marker->kn_status = KN_MARKER;
	KQ_LOCK(kq);

retry:
	kevp = keva;
	if (kq->kq_count == 0) {
		if (asbt == -1) {
			error = EWOULDBLOCK;
		} else {
			kq->kq_state |= KQ_SLEEP;
			error = msleep_sbt(kq, &kq->kq_lock, PSOCK | PCATCH,
			    "kqread", asbt, rsbt, C_ABSOLUTE);
		}
		if (error == 0)
			goto retry;
		/* don't restart after signals... */
		if (error == ERESTART)
			error = EINTR;
		else if (error == EWOULDBLOCK)
			error = 0;
		goto done;
	}

	TAILQ_INSERT_TAIL(&kq->kq_head, marker, kn_tqe);
	influx = 0;
	while (count) {
		KQ_OWNED(kq);
		kn = TAILQ_FIRST(&kq->kq_head);

		if ((kn->kn_status == KN_MARKER && kn != marker) ||
		    kn_in_flux(kn)) {
			if (influx) {
				influx = 0;
				KQ_FLUX_WAKEUP(kq);
			}
			kq->kq_state |= KQ_FLUXWAIT;
			error = msleep(kq, &kq->kq_lock, PSOCK,
			    "kqflxwt", 0);
			continue;
		}

		TAILQ_REMOVE(&kq->kq_head, kn, kn_tqe);
		if ((kn->kn_status & KN_DISABLED) == KN_DISABLED) {
			kn->kn_status &= ~KN_QUEUED;
			kq->kq_count--;
			continue;
		}
		if (kn == marker) {
			KQ_FLUX_WAKEUP(kq);
			if (count == maxevents)
				goto retry;
			goto done;
		}
		KASSERT(!kn_in_flux(kn),
		    ("knote %p is unexpectedly in flux", kn));

		if ((kn->kn_flags & EV_DROP) == EV_DROP) {
			kn->kn_status &= ~KN_QUEUED;
			kn_enter_flux(kn);
			kq->kq_count--;
			KQ_UNLOCK(kq);
			/*
			 * We don't need to lock the list since we've
			 * marked it as in flux.
			 */
			knote_drop(kn, td);
			KQ_LOCK(kq);
			continue;
		} else if ((kn->kn_flags & EV_ONESHOT) == EV_ONESHOT) {
			kn->kn_status &= ~KN_QUEUED;
			kn_enter_flux(kn);
			kq->kq_count--;
			KQ_UNLOCK(kq);
			/*
			 * We don't need to lock the list since we've
			 * marked the knote as being in flux.
			 */
			*kevp = kn->kn_kevent;
			knote_drop(kn, td);
			KQ_LOCK(kq);
			kn = NULL;
		} else {
			kn->kn_status |= KN_SCAN;
			kn_enter_flux(kn);
			KQ_UNLOCK(kq);
			if ((kn->kn_status & KN_KQUEUE) == KN_KQUEUE)
				KQ_GLOBAL_LOCK(&kq_global, haskqglobal);
			knl = kn_list_lock(kn);
			if (kn->kn_fop->f_event(kn, 0) == 0) {
				KQ_LOCK(kq);
				KQ_GLOBAL_UNLOCK(&kq_global, haskqglobal);
				kn->kn_status &= ~(KN_QUEUED | KN_ACTIVE |
				    KN_SCAN);
				kn_leave_flux(kn);
				kq->kq_count--;
				kn_list_unlock(knl);
				influx = 1;
				continue;
			}
			touch = (!kn->kn_fop->f_isfd &&
			    kn->kn_fop->f_touch != NULL);
			if (touch)
				kn->kn_fop->f_touch(kn, kevp, EVENT_PROCESS);
			else
				*kevp = kn->kn_kevent;
			KQ_LOCK(kq);
			KQ_GLOBAL_UNLOCK(&kq_global, haskqglobal);
			if (kn->kn_flags & (EV_CLEAR | EV_DISPATCH)) {
				/* 
				 * Manually clear knotes who weren't 
				 * 'touch'ed.
				 */
				if (touch == 0 && kn->kn_flags & EV_CLEAR) {
					kn->kn_data = 0;
					kn->kn_fflags = 0;
				}
				if (kn->kn_flags & EV_DISPATCH)
					kn->kn_status |= KN_DISABLED;
				kn->kn_status &= ~(KN_QUEUED | KN_ACTIVE);
				kq->kq_count--;
			} else
				TAILQ_INSERT_TAIL(&kq->kq_head, kn, kn_tqe);
			
			kn->kn_status &= ~KN_SCAN;
			kn_leave_flux(kn);
			kn_list_unlock(knl);
			influx = 1;
		}

		/* we are returning a copy to the user */
		kevp++;
		nkev++;
		count--;

		if (nkev == KQ_NEVENTS) {
			influx = 0;
			KQ_UNLOCK_FLUX(kq);
			error = k_ops->k_copyout(k_ops->arg, keva, nkev);
			nkev = 0;
			kevp = keva;
			KQ_LOCK(kq);
			if (error)
				break;
		}
	}
	TAILQ_REMOVE(&kq->kq_head, marker, kn_tqe);
done:
	KQ_OWNED(kq);
	KQ_UNLOCK_FLUX(kq);
	knote_free(marker);
done_nl:
	KQ_NOTOWNED(kq);
	if (nkev != 0)
		error = k_ops->k_copyout(k_ops->arg, keva, nkev);
	td->td_retval[0] = maxevents - count;
	return (error);
}