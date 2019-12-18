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
struct nm_selinfo {TYPE_1__ si; int /*<<< orphan*/  kqueue_users; int /*<<< orphan*/  mtxname; } ;
struct netmap_priv_d {struct nm_selinfo** np_si; struct netmap_adapter* np_na; } ;
struct netmap_adapter {int dummy; } ;
struct knote {int kn_filter; struct netmap_priv_d* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EVFILT_READ ; 
 int EVFILT_WRITE ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 size_t NR_RX ; 
 size_t NR_TX ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_rfiltops ; 
 int /*<<< orphan*/  netmap_wfiltops ; 
 int /*<<< orphan*/  nm_prerr (char*,...) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netmap_kqfilter(struct cdev *dev, struct knote *kn)
{
	struct netmap_priv_d *priv;
	int error;
	struct netmap_adapter *na;
	struct nm_selinfo *si;
	int ev = kn->kn_filter;

	if (ev != EVFILT_READ && ev != EVFILT_WRITE) {
		nm_prerr("bad filter request %d", ev);
		return 1;
	}
	error = devfs_get_cdevpriv((void**)&priv);
	if (error) {
		nm_prerr("device not yet setup");
		return 1;
	}
	na = priv->np_na;
	if (na == NULL) {
		nm_prerr("no netmap adapter for this file descriptor");
		return 1;
	}
	/* the si is indicated in the priv */
	si = priv->np_si[(ev == EVFILT_WRITE) ? NR_TX : NR_RX];
	kn->kn_fop = (ev == EVFILT_WRITE) ?
		&netmap_wfiltops : &netmap_rfiltops;
	kn->kn_hook = priv;
	NMG_LOCK();
	si->kqueue_users++;
	nm_prinf("kqueue users for %s: %d", si->mtxname, si->kqueue_users);
	NMG_UNLOCK();
	knlist_add(&si->si.si_note, kn, /*islocked=*/0);

	return 0;
}