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
typedef  int /*<<< orphan*/  uint8_t ;
struct nfsrv_descript {int nd_flag; int /*<<< orphan*/  nd_sessionid; } ;

/* Variables and functions */
 int ND_HASSEQUENCE ; 
 int ND_LASTOP ; 
 int /*<<< orphan*/  NFSBCMP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFSERR_BADSESSION ; 
 int /*<<< orphan*/  NFSLOCKV4ROOTMUTEX () ; 
 int /*<<< orphan*/  NFSUNLOCKV4ROOTMUTEX () ; 
 int /*<<< orphan*/  NFSV4ROOTLOCKMUTEXPTR ; 
 int /*<<< orphan*/  NFSX_V4SESSIONID ; 
 int nfsrv_freesession (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsv4_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_relref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfsv4rootfs_lock ; 

int
nfsrv_destroysession(struct nfsrv_descript *nd, uint8_t *sessionid)
{
	int error, igotlock, samesess;

	samesess = 0;
	if (!NFSBCMP(sessionid, nd->nd_sessionid, NFSX_V4SESSIONID) &&
	    (nd->nd_flag & ND_HASSEQUENCE) != 0) {
		samesess = 1;
		if ((nd->nd_flag & ND_LASTOP) == 0)
			return (NFSERR_BADSESSION);
	}

	/* Lock out other nfsd threads */
	NFSLOCKV4ROOTMUTEX();
	nfsv4_relref(&nfsv4rootfs_lock);
	do {
		igotlock = nfsv4_lock(&nfsv4rootfs_lock, 1, NULL,
		    NFSV4ROOTLOCKMUTEXPTR, NULL);
	} while (igotlock == 0);
	NFSUNLOCKV4ROOTMUTEX();

	error = nfsrv_freesession(NULL, sessionid);
	if (error == 0 && samesess != 0)
		nd->nd_flag &= ~ND_HASSEQUENCE;

	NFSLOCKV4ROOTMUTEX();
	nfsv4_unlock(&nfsv4rootfs_lock, 1);
	NFSUNLOCKV4ROOTMUTEX();
	return (error);
}