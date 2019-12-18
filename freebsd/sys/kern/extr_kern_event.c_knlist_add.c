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
struct knote {int kn_status; int /*<<< orphan*/  kn_kq; struct knlist* kn_knlist; } ;
struct knlist {int /*<<< orphan*/  kl_lockarg; int /*<<< orphan*/  (* kl_unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  kl_list; int /*<<< orphan*/  (* kl_lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KNL_ASSERT_LOCK (struct knlist*,int) ; 
 int KN_DETACHED ; 
 int /*<<< orphan*/  KQ_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KQ_NOTOWNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KQ_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int kn_in_flux (struct knote*) ; 
 int /*<<< orphan*/  kn_selnext ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void
knlist_add(struct knlist *knl, struct knote *kn, int islocked)
{

	KNL_ASSERT_LOCK(knl, islocked);
	KQ_NOTOWNED(kn->kn_kq);
	KASSERT(kn_in_flux(kn), ("knote %p not in flux", kn));
	KASSERT((kn->kn_status & KN_DETACHED) != 0,
	    ("knote %p was not detached", kn));
	if (!islocked)
		knl->kl_lock(knl->kl_lockarg);
	SLIST_INSERT_HEAD(&knl->kl_list, kn, kn_selnext);
	if (!islocked)
		knl->kl_unlock(knl->kl_lockarg);
	KQ_LOCK(kn->kn_kq);
	kn->kn_knlist = knl;
	kn->kn_status &= ~KN_DETACHED;
	KQ_UNLOCK(kn->kn_kq);
}