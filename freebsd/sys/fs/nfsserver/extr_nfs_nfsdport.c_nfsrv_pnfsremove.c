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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct ucred {int dummy; } ;
struct nfsrvdsremove {scalar_t__ inprog; scalar_t__ done; int err; int /*<<< orphan*/  tsk; int /*<<< orphan*/  fname; struct vnode* dvp; int /*<<< orphan*/ * p; struct ucred* tcred; } ;
struct nfsmount {int nm_privflag; } ;
struct nfsdevice {int dummy; } ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,int,...) ; 
 int /*<<< orphan*/  NFSFREECRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSLOCKMNT (struct nfsmount*) ; 
 int NFSMNTP_CANCELRPCS ; 
 int NFSMNTP_FORCEDISM ; 
 int /*<<< orphan*/  NFSUNLOCKMNT (struct nfsmount*) ; 
 int /*<<< orphan*/  PNFSDOP_DELDSSERVER ; 
 scalar_t__ PNFS_FILENAME_LEN ; 
 int /*<<< orphan*/  PVFS ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nfsrvdsremove*,int /*<<< orphan*/ ) ; 
 int hz ; 
 struct nfsrvdsremove* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ucred* newnfs_getcred () ; 
 int nfs_pnfsio (int /*<<< orphan*/ ,struct nfsrvdsremove*) ; 
 scalar_t__ nfs_pnfsiothreads ; 
 scalar_t__ nfsds_failerr (int) ; 
 struct nfsdevice* nfsrv_deldsnmp (int /*<<< orphan*/ ,struct nfsmount*,int /*<<< orphan*/ *) ; 
 int nfsrv_dsremove (struct vnode*,char*,struct ucred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_freefilelayouts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_killrpcs (struct nfsmount*) ; 
 int /*<<< orphan*/  start_dsremove ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (struct nfsmount*) ; 

__attribute__((used)) static void
nfsrv_pnfsremove(struct vnode **dvp, int mirrorcnt, char *fname, fhandle_t *fhp,
    NFSPROC_T *p)
{
	struct ucred *tcred;
	struct nfsrvdsremove *dsrm, *tdsrm;
	struct nfsdevice *ds;
	struct nfsmount *nmp;
	int failpos, i, ret, timo;

	tcred = newnfs_getcred();
	dsrm = NULL;
	if (mirrorcnt > 1)
		dsrm = malloc(sizeof(*dsrm) * mirrorcnt - 1, M_TEMP, M_WAITOK);
	/*
	 * Remove the file on each DS mirror, using kernel process(es) for the
	 * additional mirrors.
	 */
	failpos = -1;
	for (tdsrm = dsrm, i = 0; i < mirrorcnt - 1; i++, tdsrm++) {
		tdsrm->tcred = tcred;
		tdsrm->p = p;
		tdsrm->dvp = dvp[i];
		strlcpy(tdsrm->fname, fname, PNFS_FILENAME_LEN + 1);
		tdsrm->inprog = 0;
		tdsrm->done = 0;
		tdsrm->err = 0;
		ret = EIO;
		if (nfs_pnfsiothreads != 0) {
			ret = nfs_pnfsio(start_dsremove, tdsrm);
			NFSD_DEBUG(4, "nfsrv_pnfsremove: nfs_pnfsio=%d\n", ret);
		}
		if (ret != 0) {
			ret = nfsrv_dsremove(dvp[i], fname, tcred, p);
			if (failpos == -1 && nfsds_failerr(ret))
				failpos = i;
		}
	}
	ret = nfsrv_dsremove(dvp[mirrorcnt - 1], fname, tcred, p);
	if (failpos == -1 && mirrorcnt > 1 && nfsds_failerr(ret))
		failpos = mirrorcnt - 1;
	timo = hz / 50;		/* Wait for 20msec. */
	if (timo < 1)
		timo = 1;
	/* Wait for kernel task(s) to complete. */
	for (tdsrm = dsrm, i = 0; i < mirrorcnt - 1; i++, tdsrm++) {
		while (tdsrm->inprog != 0 && tdsrm->done == 0)
			tsleep(&tdsrm->tsk, PVFS, "srvdsrm", timo);
		if (failpos == -1 && nfsds_failerr(tdsrm->err))
			failpos = i;
	}

	/*
	 * If failpos has been set, that mirror has failed, so it needs
	 * to be disabled.
	 */
	if (failpos >= 0) {
		nmp = VFSTONFS(dvp[failpos]->v_mount);
		NFSLOCKMNT(nmp);
		if ((nmp->nm_privflag & (NFSMNTP_FORCEDISM |
		     NFSMNTP_CANCELRPCS)) == 0) {
			nmp->nm_privflag |= NFSMNTP_CANCELRPCS;
			NFSUNLOCKMNT(nmp);
			ds = nfsrv_deldsnmp(PNFSDOP_DELDSSERVER, nmp, p);
			NFSD_DEBUG(4, "dsremovefail fail=%d ds=%p\n", failpos,
			    ds);
			if (ds != NULL)
				nfsrv_killrpcs(nmp);
			NFSLOCKMNT(nmp);
			nmp->nm_privflag &= ~NFSMNTP_CANCELRPCS;
			wakeup(nmp);
		}
		NFSUNLOCKMNT(nmp);
	}

	/* Get rid all layouts for the file. */
	nfsrv_freefilelayouts(fhp);

	NFSFREECRED(tcred);
	free(dsrm, M_TEMP);
}