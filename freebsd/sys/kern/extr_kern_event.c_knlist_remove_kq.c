#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knote {int kn_status; TYPE_1__* kn_kq; int /*<<< orphan*/ * kn_knlist; } ;
struct knlist {int /*<<< orphan*/  kl_list; int /*<<< orphan*/  kl_lockarg; int /*<<< orphan*/  (* kl_lock ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  kq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KNL_ASSERT_LOCK (struct knlist*,int) ; 
 int KN_DETACHED ; 
 int /*<<< orphan*/  KQ_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  KQ_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kn_in_flux (struct knote*) ; 
 int /*<<< orphan*/  kn_list_unlock (struct knlist*) ; 
 int /*<<< orphan*/  kn_selnext ; 
 int /*<<< orphan*/  knote ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
knlist_remove_kq(struct knlist *knl, struct knote *kn, int knlislocked,
    int kqislocked)
{

	KASSERT(!kqislocked || knlislocked, ("kq locked w/o knl locked"));
	KNL_ASSERT_LOCK(knl, knlislocked);
	mtx_assert(&kn->kn_kq->kq_lock, kqislocked ? MA_OWNED : MA_NOTOWNED);
	KASSERT(kqislocked || kn_in_flux(kn), ("knote %p not in flux", kn));
	KASSERT((kn->kn_status & KN_DETACHED) == 0,
	    ("knote %p was already detached", kn));
	if (!knlislocked)
		knl->kl_lock(knl->kl_lockarg);
	SLIST_REMOVE(&knl->kl_list, kn, knote, kn_selnext);
	kn->kn_knlist = NULL;
	if (!knlislocked)
		kn_list_unlock(knl);
	if (!kqislocked)
		KQ_LOCK(kn->kn_kq);
	kn->kn_status |= KN_DETACHED;
	if (!kqislocked)
		KQ_UNLOCK(kn->kn_kq);
}