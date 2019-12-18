#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {scalar_t__ uio_offset; TYPE_2__* uio_iov; scalar_t__ uio_resid; } ;
struct ucred {int dummy; } ;
struct nfsnode {int n_flag; TYPE_3__* n_fhp; } ;
struct nfsmount {int /*<<< orphan*/  nm_state; int /*<<< orphan*/  nm_clp; } ;
struct nfsclwritedsdorpc {scalar_t__ inprog; scalar_t__ done; int err; int /*<<< orphan*/  tsk; } ;
struct nfscllayout {int nfsly_flags; scalar_t__ nfsly_lastbyte; } ;
struct nfsclflayout {scalar_t__ nfsfl_end; scalar_t__ nfsfl_off; int nfsfl_mirrorcnt; int nfsfl_flags; int /*<<< orphan*/  nfsfl_devp; int /*<<< orphan*/ * nfsfl_dev; TYPE_1__* nfsfl_ffm; } ;
struct nfscldevinfo {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
struct TYPE_6__ {int /*<<< orphan*/  nfh_len; int /*<<< orphan*/  nfh_fh; } ;
struct TYPE_5__ {size_t iov_len; void* iov_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  devp; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NFSERR_OPENMODE ; 
 int NFSFL_FLEXFILE ; 
 int /*<<< orphan*/  NFSFREECRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSHASPNFS (struct nfsmount*) ; 
 int NFSLAYOUTIOMODE_READ ; 
 int NFSLAYOUTIOMODE_RW ; 
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSLOCKMNT (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int NFSLY_FLEXFILE ; 
 int NFSLY_WRITTEN ; 
 struct ucred* NFSNEWCRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSSTA_OPENMODE ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKMNT (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSV4OPEN_ACCESSREAD ; 
 int /*<<< orphan*/  NFSV4OPEN_ACCESSWRITE ; 
 int NNOLAYOUT ; 
 int NWRITEOPENED ; 
 int /*<<< orphan*/  PVFS ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 struct nfsnode* VTONFS (int /*<<< orphan*/ ) ; 
 int arc4random () ; 
 int /*<<< orphan*/  free (struct nfsclwritedsdorpc*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct nfsclwritedsdorpc* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfs_numnfscbd ; 
 int nfscl_dofflayoutio (int /*<<< orphan*/ ,struct uio*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfscldevinfo*,struct nfscllayout*,struct nfsclflayout*,scalar_t__,scalar_t__,int,int,struct mbuf*,struct nfsclwritedsdorpc*,struct ucred*,int /*<<< orphan*/ *) ; 
 int nfscl_doflayoutio (int /*<<< orphan*/ ,struct uio*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfscldevinfo*,struct nfscllayout*,struct nfsclflayout*,scalar_t__,scalar_t__,int,struct ucred*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfscl_enablecallb ; 
 int nfscl_findlayoutforio (struct nfscllayout*,scalar_t__,int /*<<< orphan*/ ,struct nfsclflayout**) ; 
 struct nfscldevinfo* nfscl_getdevinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfscllayout* nfscl_getlayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct nfsclflayout**,int*) ; 
 scalar_t__ nfscl_getref (struct nfsmount*) ; 
 int nfscl_getstateid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nfscl_lockderef (void*) ; 
 int /*<<< orphan*/  nfscl_reldevinfo (struct nfscldevinfo*) ; 
 int /*<<< orphan*/  nfscl_rellayout (struct nfscllayout*,int) ; 
 int /*<<< orphan*/  nfscl_relref (struct nfsmount*) ; 
 struct mbuf* nfsm_uiombuflist (struct uio*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsrpc_getlayout (struct nfsmount*,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,struct nfscllayout**,struct ucred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ ) ; 

int
nfscl_doiods(vnode_t vp, struct uio *uiop, int *iomode, int *must_commit,
    uint32_t rwaccess, int docommit, struct ucred *cred, NFSPROC_T *p)
{
	struct nfsnode *np = VTONFS(vp);
	struct nfsmount *nmp = VFSTONFS(vnode_mount(vp));
	struct nfscllayout *layp;
	struct nfscldevinfo *dip;
	struct nfsclflayout *rflp;
	struct mbuf *m;
	struct nfsclwritedsdorpc *drpc, *tdrpc;
	nfsv4stateid_t stateid;
	struct ucred *newcred;
	uint64_t lastbyte, len, off, oresid, xfer;
	int eof, error, firstmirror, i, iolaymode, mirrorcnt, recalled, timo;
	void *lckp;
	uint8_t *dev;
	void *iovbase = NULL;
	size_t iovlen = 0;
	off_t offs = 0;
	ssize_t resid = 0;

	if (!NFSHASPNFS(nmp) || nfscl_enablecallb == 0 || nfs_numnfscbd == 0 ||
	    (np->n_flag & NNOLAYOUT) != 0)
		return (EIO);
	/* Now, get a reference cnt on the clientid for this mount. */
	if (nfscl_getref(nmp) == 0)
		return (EIO);

	/* Find an appropriate stateid. */
	newcred = NFSNEWCRED(cred);
	error = nfscl_getstateid(vp, np->n_fhp->nfh_fh, np->n_fhp->nfh_len,
	    rwaccess, 1, newcred, p, &stateid, &lckp);
	if (error != 0) {
		NFSFREECRED(newcred);
		nfscl_relref(nmp);
		return (error);
	}
	/* Search for a layout for this file. */
	off = uiop->uio_offset;
	layp = nfscl_getlayout(nmp->nm_clp, np->n_fhp->nfh_fh,
	    np->n_fhp->nfh_len, off, &rflp, &recalled);
	if (layp == NULL || rflp == NULL) {
		if (recalled != 0) {
			NFSFREECRED(newcred);
			nfscl_relref(nmp);
			return (EIO);
		}
		if (layp != NULL) {
			nfscl_rellayout(layp, (rflp == NULL) ? 1 : 0);
			layp = NULL;
		}
		/* Try and get a Layout, if it is supported. */
		if (rwaccess == NFSV4OPEN_ACCESSWRITE ||
		    (np->n_flag & NWRITEOPENED) != 0)
			iolaymode = NFSLAYOUTIOMODE_RW;
		else
			iolaymode = NFSLAYOUTIOMODE_READ;
		error = nfsrpc_getlayout(nmp, vp, np->n_fhp, iolaymode,
		    NULL, &stateid, off, &layp, newcred, p);
		if (error != 0) {
			NFSLOCKNODE(np);
			np->n_flag |= NNOLAYOUT;
			NFSUNLOCKNODE(np);
			if (lckp != NULL)
				nfscl_lockderef(lckp);
			NFSFREECRED(newcred);
			if (layp != NULL)
				nfscl_rellayout(layp, 0);
			nfscl_relref(nmp);
			return (error);
		}
	}

	/*
	 * Loop around finding a layout that works for the first part of
	 * this I/O operation, and then call the function that actually
	 * does the RPC.
	 */
	eof = 0;
	len = (uint64_t)uiop->uio_resid;
	while (len > 0 && error == 0 && eof == 0) {
		off = uiop->uio_offset;
		error = nfscl_findlayoutforio(layp, off, rwaccess, &rflp);
		if (error == 0) {
			oresid = xfer = (uint64_t)uiop->uio_resid;
			if (xfer > (rflp->nfsfl_end - rflp->nfsfl_off))
				xfer = rflp->nfsfl_end - rflp->nfsfl_off;
			/*
			 * For Flex File layout with mirrored DSs, select one
			 * of them at random for reads. For writes and commits,
			 * do all mirrors.
			 */
			m = NULL;
			tdrpc = drpc = NULL;
			firstmirror = 0;
			mirrorcnt = 1;
			if ((layp->nfsly_flags & NFSLY_FLEXFILE) != 0 &&
			    (mirrorcnt = rflp->nfsfl_mirrorcnt) > 1) {
				if (rwaccess == NFSV4OPEN_ACCESSREAD) {
					firstmirror = arc4random() % mirrorcnt;
					mirrorcnt = firstmirror + 1;
				} else {
					if (docommit == 0) {
						/*
						 * Save values, so uiop can be
						 * rolled back upon a write
						 * error.
						 */
						offs = uiop->uio_offset;
						resid = uiop->uio_resid;
						iovbase =
						    uiop->uio_iov->iov_base;
						iovlen = uiop->uio_iov->iov_len;
						m = nfsm_uiombuflist(uiop, len,
						    NULL, NULL);
					}
					tdrpc = drpc = malloc(sizeof(*drpc) *
					    (mirrorcnt - 1), M_TEMP, M_WAITOK |
					    M_ZERO);
				}
			}
			for (i = firstmirror; i < mirrorcnt && error == 0; i++){
				if ((layp->nfsly_flags & NFSLY_FLEXFILE) != 0) {
					dev = rflp->nfsfl_ffm[i].dev;
					dip = nfscl_getdevinfo(nmp->nm_clp, dev,
					    rflp->nfsfl_ffm[i].devp);
				} else {
					dev = rflp->nfsfl_dev;
					dip = nfscl_getdevinfo(nmp->nm_clp, dev,
					    rflp->nfsfl_devp);
				}
				if (dip != NULL) {
					if ((rflp->nfsfl_flags & NFSFL_FLEXFILE)
					    != 0)
						error = nfscl_dofflayoutio(vp,
						    uiop, iomode, must_commit,
						    &eof, &stateid, rwaccess,
						    dip, layp, rflp, off, xfer,
						    i, docommit, m, tdrpc,
						    newcred, p);
					else
						error = nfscl_doflayoutio(vp,
						    uiop, iomode, must_commit,
						    &eof, &stateid, rwaccess,
						    dip, layp, rflp, off, xfer,
						    docommit, newcred, p);
					nfscl_reldevinfo(dip);
				} else
					error = EIO;
				tdrpc++;
			}
			if (m != NULL)
				m_freem(m);
			tdrpc = drpc;
			timo = hz / 50;		/* Wait for 20msec. */
			if (timo < 1)
				timo = 1;
			for (i = firstmirror; i < mirrorcnt - 1 &&
			    tdrpc != NULL; i++, tdrpc++) {
				/*
				 * For the unused drpc entries, both inprog and
				 * err == 0, so this loop won't break.
				 */
				while (tdrpc->inprog != 0 && tdrpc->done == 0)
					tsleep(&tdrpc->tsk, PVFS, "clrpcio",
					    timo);
				if (error == 0 && tdrpc->err != 0)
					error = tdrpc->err;
			}
			free(drpc, M_TEMP);
			if (error == 0) {
				if (mirrorcnt > 1 && rwaccess ==
				    NFSV4OPEN_ACCESSWRITE && docommit == 0) {
					NFSLOCKCLSTATE();
					layp->nfsly_flags |= NFSLY_WRITTEN;
					NFSUNLOCKCLSTATE();
				}
				lastbyte = off + xfer - 1;
				NFSLOCKCLSTATE();
				if (lastbyte > layp->nfsly_lastbyte)
					layp->nfsly_lastbyte = lastbyte;
				NFSUNLOCKCLSTATE();
			} else if (error == NFSERR_OPENMODE &&
			    rwaccess == NFSV4OPEN_ACCESSREAD) {
				NFSLOCKMNT(nmp);
				nmp->nm_state |= NFSSTA_OPENMODE;
				NFSUNLOCKMNT(nmp);
			} else
				error = EIO;
			if (error == 0)
				len -= (oresid - (uint64_t)uiop->uio_resid);
			else if (mirrorcnt > 1 && rwaccess ==
			    NFSV4OPEN_ACCESSWRITE && docommit == 0) {
				/*
				 * In case the rpc gets retried, roll the
				 * uio fields changed by nfsm_uiombuflist()
				 * back.
				 */
				uiop->uio_offset = offs;
				uiop->uio_resid = resid;
				uiop->uio_iov->iov_base = iovbase;
				uiop->uio_iov->iov_len = iovlen;
			}
		}
	}
	if (lckp != NULL)
		nfscl_lockderef(lckp);
	NFSFREECRED(newcred);
	nfscl_rellayout(layp, 0);
	nfscl_relref(nmp);
	return (error);
}