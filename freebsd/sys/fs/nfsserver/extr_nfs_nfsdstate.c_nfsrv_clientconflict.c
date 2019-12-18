#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct nfsclient {scalar_t__ lc_expiry; int /*<<< orphan*/  lc_olddeleg; int /*<<< orphan*/  lc_deleg; int /*<<< orphan*/  lc_idlen; int /*<<< orphan*/  lc_id; } ;
struct TYPE_8__ {int nsf_flags; } ;
struct TYPE_7__ {int v_iflag; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfsclient*,int /*<<< orphan*/ ) ; 
 int LK_RETRY ; 
 scalar_t__ NFSD_MONOSEC ; 
 int /*<<< orphan*/  NFSLOCKV4ROOTMUTEX () ; 
 int NFSNSF_UPDATEDONE ; 
 int /*<<< orphan*/  NFSNST_REVOKE ; 
 int /*<<< orphan*/  NFSUNLOCKSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKV4ROOTMUTEX () ; 
 int /*<<< orphan*/  NFSV4ROOTLOCKMUTEXPTR ; 
 int NFSVOPISLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  NFSVOPLOCK (TYPE_1__*,int) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  lc_hash ; 
 int /*<<< orphan*/  nfsrv_backupstable () ; 
 int /*<<< orphan*/  nfsrv_cleanclient (struct nfsclient*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_freedeleglist (int /*<<< orphan*/ *) ; 
 TYPE_2__ nfsrv_stablefirst ; 
 int /*<<< orphan*/  nfsrv_writestable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_zapclient (struct nfsclient*,int /*<<< orphan*/ *) ; 
 int nfsv4_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_relref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4rootfs_lock ; 

__attribute__((used)) static int
nfsrv_clientconflict(struct nfsclient *clp, int *haslockp, vnode_t vp,
    NFSPROC_T *p)
{
	int gotlock, lktype = 0;

	/*
	 * If lease hasn't expired, we can't fix it.
	 */
	if (clp->lc_expiry >= NFSD_MONOSEC ||
	    !(nfsrv_stablefirst.nsf_flags & NFSNSF_UPDATEDONE))
		return (0);
	if (*haslockp == 0) {
		NFSUNLOCKSTATE();
		if (vp != NULL) {
			lktype = NFSVOPISLOCKED(vp);
			NFSVOPUNLOCK(vp, 0);
		}
		NFSLOCKV4ROOTMUTEX();
		nfsv4_relref(&nfsv4rootfs_lock);
		do {
			gotlock = nfsv4_lock(&nfsv4rootfs_lock, 1, NULL,
			    NFSV4ROOTLOCKMUTEXPTR, NULL);
		} while (!gotlock);
		NFSUNLOCKV4ROOTMUTEX();
		*haslockp = 1;
		if (vp != NULL) {
			NFSVOPLOCK(vp, lktype | LK_RETRY);
			if ((vp->v_iflag & VI_DOOMED) != 0)
				return (2);
		}
		return (1);
	}
	NFSUNLOCKSTATE();

	/*
	 * Ok, we can expire the conflicting client.
	 */
	nfsrv_writestable(clp->lc_id, clp->lc_idlen, NFSNST_REVOKE, p);
	nfsrv_backupstable();
	nfsrv_cleanclient(clp, p);
	nfsrv_freedeleglist(&clp->lc_deleg);
	nfsrv_freedeleglist(&clp->lc_olddeleg);
	LIST_REMOVE(clp, lc_hash);
	nfsrv_zapclient(clp, p);
	return (1);
}