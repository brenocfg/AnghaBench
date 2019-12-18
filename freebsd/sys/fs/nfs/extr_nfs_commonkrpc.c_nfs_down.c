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
struct nfsmount {int nm_state; TYPE_2__* nm_mountp; int /*<<< orphan*/  nm_mtx; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_fsid; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int NFSSTA_LOCKTIMEO ; 
 int NFSSTA_TIMEO ; 
 int /*<<< orphan*/  VQ_NOTRESP ; 
 int /*<<< orphan*/  VQ_NOTRESPLOCK ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_msg (struct thread*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vfs_event_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_down(struct nfsmount *nmp, struct thread *td, const char *msg,
    int error, int flags)
{
	if (nmp == NULL)
		return;
	mtx_lock(&nmp->nm_mtx);
	if ((flags & NFSSTA_TIMEO) && !(nmp->nm_state & NFSSTA_TIMEO)) {
		nmp->nm_state |= NFSSTA_TIMEO;
		mtx_unlock(&nmp->nm_mtx);
		vfs_event_signal(&nmp->nm_mountp->mnt_stat.f_fsid,
		    VQ_NOTRESP, 0);
	} else
		mtx_unlock(&nmp->nm_mtx);
	mtx_lock(&nmp->nm_mtx);
	if ((flags & NFSSTA_LOCKTIMEO) && !(nmp->nm_state & NFSSTA_LOCKTIMEO)) {
		nmp->nm_state |= NFSSTA_LOCKTIMEO;
		mtx_unlock(&nmp->nm_mtx);
		vfs_event_signal(&nmp->nm_mountp->mnt_stat.f_fsid,
		    VQ_NOTRESPLOCK, 0);
	} else
		mtx_unlock(&nmp->nm_mtx);
	nfs_msg(td, nmp->nm_mountp->mnt_stat.f_mntfromname, msg, error);
}