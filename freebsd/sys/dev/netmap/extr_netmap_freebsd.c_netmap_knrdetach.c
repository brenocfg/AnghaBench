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
struct nm_selinfo {scalar_t__ kqueue_users; int /*<<< orphan*/  mtxname; TYPE_1__ si; } ;
struct netmap_priv_d {struct nm_selinfo** np_si; } ;
struct knote {scalar_t__ kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 size_t NR_RX ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
netmap_knrdetach(struct knote *kn)
{
	struct netmap_priv_d *priv = (struct netmap_priv_d *)kn->kn_hook;
	struct nm_selinfo *si = priv->np_si[NR_RX];

	knlist_remove(&si->si.si_note, kn, /*islocked=*/0);
	NMG_LOCK();
	KASSERT(si->kqueue_users > 0, ("kqueue_user underflow on %s",
	    si->mtxname));
	si->kqueue_users--;
	nm_prinf("kqueue users for %s: %d", si->mtxname, si->kqueue_users);
	NMG_UNLOCK();
}