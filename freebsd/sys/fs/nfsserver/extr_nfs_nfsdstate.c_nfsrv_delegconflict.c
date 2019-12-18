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
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  tstateid ;
typedef  int /*<<< orphan*/  tfh ;
struct nfsstate {int ls_flags; scalar_t__ ls_delegtime; TYPE_1__* ls_lfp; int /*<<< orphan*/  ls_stateid; scalar_t__ ls_delegtimelimit; struct nfsclient* ls_clp; } ;
struct nfsclient {scalar_t__ lc_delegtime; scalar_t__ lc_expiry; int /*<<< orphan*/  lc_olddeleg; int /*<<< orphan*/  lc_deleg; int /*<<< orphan*/  lc_idlen; int /*<<< orphan*/  lc_id; } ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {int v_iflag; } ;
struct TYPE_7__ {int /*<<< orphan*/  lf_fh; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfsclient*,int /*<<< orphan*/ ) ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  NFSBCOPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NFSD_MONOSEC ; 
 int NFSERR_BADHANDLE ; 
 int NFSERR_BADSTATEID ; 
 int NFSERR_DELAY ; 
 int NFSERR_PERM ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int NFSLCK_DELEGRECALL ; 
 int NFSLCK_OLDDELEG ; 
 int /*<<< orphan*/  NFSLOCKV4ROOTMUTEX () ; 
 int /*<<< orphan*/  NFSNST_REVOKE ; 
 scalar_t__ NFSRV_LEASEDELTA ; 
 int /*<<< orphan*/  NFSUNLOCKSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKV4ROOTMUTEX () ; 
 int /*<<< orphan*/  NFSV4OP_CBRECALL ; 
 int /*<<< orphan*/  NFSV4ROOTLOCKMUTEXPTR ; 
 int NFSV4_CBRETRYCNT ; 
 int NFSVOPISLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSVOPLOCK (TYPE_2__*,int) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  lc_hash ; 
 int /*<<< orphan*/  nfsrv_backupstable () ; 
 int /*<<< orphan*/  nfsrv_cleanclient (struct nfsclient*,int /*<<< orphan*/ *) ; 
 int nfsrv_docallback (struct nfsclient*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_freedeleg (struct nfsstate*) ; 
 int /*<<< orphan*/  nfsrv_freedeleglist (int /*<<< orphan*/ *) ; 
 int nfsrv_lease ; 
 int /*<<< orphan*/  nfsrv_writestable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_zapclient (struct nfsclient*,int /*<<< orphan*/ *) ; 
 int nfsv4_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_relref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfsv4rootfs_lock ; 

__attribute__((used)) static int
nfsrv_delegconflict(struct nfsstate *stp, int *haslockp, NFSPROC_T *p,
    vnode_t vp)
{
	struct nfsclient *clp = stp->ls_clp;
	int gotlock, error, lktype = 0, retrycnt, zapped_clp;
	nfsv4stateid_t tstateid;
	fhandle_t tfh;

	/*
	 * If the conflict is with an old delegation...
	 */
	if (stp->ls_flags & NFSLCK_OLDDELEG) {
		/*
		 * You can delete it, if it has expired.
		 */
		if (clp->lc_delegtime < NFSD_MONOSEC) {
			nfsrv_freedeleg(stp);
			NFSUNLOCKSTATE();
			error = -1;
			goto out;
		}
		NFSUNLOCKSTATE();
		/*
		 * During this delay, the old delegation could expire or it
		 * could be recovered by the client via an Open with
		 * CLAIM_DELEGATE_PREV.
		 * Release the nfsv4root_lock, if held.
		 */
		if (*haslockp) {
			*haslockp = 0;
			NFSLOCKV4ROOTMUTEX();
			nfsv4_unlock(&nfsv4rootfs_lock, 1);
			NFSUNLOCKV4ROOTMUTEX();
		}
		error = NFSERR_DELAY;
		goto out;
	}

	/*
	 * It's a current delegation, so:
	 * - check to see if the delegation has expired
	 *   - if so, get the v4root lock and then expire it
	 */
	if (!(stp->ls_flags & NFSLCK_DELEGRECALL)) {
		/*
		 * - do a recall callback, since not yet done
		 * For now, never allow truncate to be set. To use
		 * truncate safely, it must be guaranteed that the
		 * Remove, Rename or Setattr with size of 0 will
		 * succeed and that would require major changes to
		 * the VFS/Vnode OPs.
		 * Set the expiry time large enough so that it won't expire
		 * until after the callback, then set it correctly, once
		 * the callback is done. (The delegation will now time
		 * out whether or not the Recall worked ok. The timeout
		 * will be extended when ops are done on the delegation
		 * stateid, up to the timelimit.)
		 */
		stp->ls_delegtime = NFSD_MONOSEC + (2 * nfsrv_lease) +
		    NFSRV_LEASEDELTA;
		stp->ls_delegtimelimit = NFSD_MONOSEC + (6 * nfsrv_lease) +
		    NFSRV_LEASEDELTA;
		stp->ls_flags |= NFSLCK_DELEGRECALL;

		/*
		 * Loop NFSRV_CBRETRYCNT times while the CBRecall replies
		 * NFSERR_BADSTATEID or NFSERR_BADHANDLE. This is done
		 * in order to try and avoid a race that could happen
		 * when a CBRecall request passed the Open reply with
		 * the delegation in it when transitting the network.
		 * Since nfsrv_docallback will sleep, don't use stp after
		 * the call.
		 */
		NFSBCOPY((caddr_t)&stp->ls_stateid, (caddr_t)&tstateid,
		    sizeof (tstateid));
		NFSBCOPY((caddr_t)&stp->ls_lfp->lf_fh, (caddr_t)&tfh,
		    sizeof (tfh));
		NFSUNLOCKSTATE();
		if (*haslockp) {
			*haslockp = 0;
			NFSLOCKV4ROOTMUTEX();
			nfsv4_unlock(&nfsv4rootfs_lock, 1);
			NFSUNLOCKV4ROOTMUTEX();
		}
		retrycnt = 0;
		do {
		    error = nfsrv_docallback(clp, NFSV4OP_CBRECALL,
			&tstateid, 0, &tfh, NULL, NULL, 0, p);
		    retrycnt++;
		} while ((error == NFSERR_BADSTATEID ||
		    error == NFSERR_BADHANDLE) && retrycnt < NFSV4_CBRETRYCNT);
		error = NFSERR_DELAY;
		goto out;
	}

	if (clp->lc_expiry >= NFSD_MONOSEC &&
	    stp->ls_delegtime >= NFSD_MONOSEC) {
		NFSUNLOCKSTATE();
		/*
		 * A recall has been done, but it has not yet expired.
		 * So, RETURN_DELAY.
		 */
		if (*haslockp) {
			*haslockp = 0;
			NFSLOCKV4ROOTMUTEX();
			nfsv4_unlock(&nfsv4rootfs_lock, 1);
			NFSUNLOCKV4ROOTMUTEX();
		}
		error = NFSERR_DELAY;
		goto out;
	}

	/*
	 * If we don't yet have the lock, just get it and then return,
	 * since we need that before deleting expired state, such as
	 * this delegation.
	 * When getting the lock, unlock the vnode, so other nfsds that
	 * are in progress, won't get stuck waiting for the vnode lock.
	 */
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
			if ((vp->v_iflag & VI_DOOMED) != 0) {
				*haslockp = 0;
				NFSLOCKV4ROOTMUTEX();
				nfsv4_unlock(&nfsv4rootfs_lock, 1);
				NFSUNLOCKV4ROOTMUTEX();
				error = NFSERR_PERM;
				goto out;
			}
		}
		error = -1;
		goto out;
	}

	NFSUNLOCKSTATE();
	/*
	 * Ok, we can delete the expired delegation.
	 * First, write the Revoke record to stable storage and then
	 * clear out the conflict.
	 * Since all other nfsd threads are now blocked, we can safely
	 * sleep without the state changing.
	 */
	nfsrv_writestable(clp->lc_id, clp->lc_idlen, NFSNST_REVOKE, p);
	nfsrv_backupstable();
	if (clp->lc_expiry < NFSD_MONOSEC) {
		nfsrv_cleanclient(clp, p);
		nfsrv_freedeleglist(&clp->lc_deleg);
		nfsrv_freedeleglist(&clp->lc_olddeleg);
		LIST_REMOVE(clp, lc_hash);
		zapped_clp = 1;
	} else {
		nfsrv_freedeleg(stp);
		zapped_clp = 0;
	}
	if (zapped_clp)
		nfsrv_zapclient(clp, p);
	error = -1;

out:
	NFSEXITCODE(error);
	return (error);
}