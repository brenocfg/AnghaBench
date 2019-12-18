#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct uio {scalar_t__ uio_resid; } ;
struct ucred {int cr_ngroups; int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_uid; } ;
struct nfsnode {int /*<<< orphan*/  n_flag; } ;
struct nfsfh {int /*<<< orphan*/  nfh_len; } ;
struct nfsclwritedsdorpc {int dummy; } ;
struct nfscllayout {int /*<<< orphan*/  nfsly_flags; } ;
struct nfsclflayout {int nfsfl_mirrorcnt; TYPE_1__* nfsfl_ffm; } ;
struct nfsclds {int dummy; } ;
struct nfscldevinfo {size_t nfsdi_versindex; int nfsdi_flags; scalar_t__ nfsdi_rsize; scalar_t__ nfsdi_wsize; int /*<<< orphan*/  nfsdi_minorvers; int /*<<< orphan*/  nfsdi_vers; } ;
struct mbuf {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_2__ nfsv4stateid_t ;
struct TYPE_8__ {int /*<<< orphan*/  group; int /*<<< orphan*/  user; TYPE_2__ st; struct nfsfh** fh; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EACCES ; 
 int ESTALE ; 
 int /*<<< orphan*/  NDSCOMMIT ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,...) ; 
 int NFSDI_TIGHTCOUPLED ; 
 int /*<<< orphan*/  NFSFREECRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSLY_WRITTEN ; 
 struct ucred* NFSNEWCRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFSV4OPEN_ACCESSREAD ; 
 int /*<<< orphan*/  NFSV4OP_COMMIT ; 
 int /*<<< orphan*/  NFSV4OP_READ ; 
 int /*<<< orphan*/  NFSV4OP_WRITE ; 
 struct nfsnode* VTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_dserr (int /*<<< orphan*/ ,int,struct nfscldevinfo*,struct nfscllayout*,struct nfsclds*) ; 
 struct nfsclds** nfsfldi_addr (struct nfscldevinfo*,int /*<<< orphan*/ ) ; 
 int nfsio_commitds (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct nfsclds*,struct nfsfh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsclwritedsdorpc*,struct ucred*,int /*<<< orphan*/ *) ; 
 int nfsio_writedsmir (int /*<<< orphan*/ ,int*,int*,TYPE_2__*,struct nfsclds*,scalar_t__,scalar_t__,struct nfsfh*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsclwritedsdorpc*,struct ucred*,int /*<<< orphan*/ *) ; 
 struct mbuf* nfsm_copym (struct mbuf*,int,scalar_t__) ; 
 int nfsrpc_commitds (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct nfsclds*,struct nfsfh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 
 int nfsrpc_readds (int /*<<< orphan*/ ,struct uio*,TYPE_2__*,int*,struct nfsclds*,scalar_t__,scalar_t__,struct nfsfh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 
 int nfsrpc_writeds (int /*<<< orphan*/ ,struct uio*,int*,int*,TYPE_2__*,struct nfsclds*,scalar_t__,scalar_t__,struct nfsfh*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 
 int nfsrpc_writedsmir (int /*<<< orphan*/ ,int*,int*,TYPE_2__*,struct nfsclds*,scalar_t__,scalar_t__,struct nfsfh*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfscl_dofflayoutio(vnode_t vp, struct uio *uiop, int *iomode, int *must_commit,
    int *eofp, nfsv4stateid_t *stateidp, int rwflag, struct nfscldevinfo *dp,
    struct nfscllayout *lyp, struct nfsclflayout *flp, uint64_t off,
    uint64_t len, int mirror, int docommit, struct mbuf *mp,
    struct nfsclwritedsdorpc *drpc, struct ucred *cred, NFSPROC_T *p)
{
	uint64_t transfer, xfer;
	int error, rel_off;
	struct nfsnode *np;
	struct nfsfh *fhp;
	struct nfsclds **dspp;
	struct ucred *tcred;
	struct mbuf *m;

	np = VTONFS(vp);
	error = 0;
	rel_off = 0;
	NFSCL_DEBUG(4, "nfscl_dofflayoutio: off=%ju len=%ju\n", (uintmax_t)off,
	    (uintmax_t)len);
	/* Loop around, doing I/O for each stripe unit. */
	while (len > 0 && error == 0) {
		dspp = nfsfldi_addr(dp, 0);
		fhp = flp->nfsfl_ffm[mirror].fh[dp->nfsdi_versindex];
		stateidp = &flp->nfsfl_ffm[mirror].st;
		NFSCL_DEBUG(4, "mirror=%d vind=%d fhlen=%d st.seqid=0x%x\n",
		    mirror, dp->nfsdi_versindex, fhp->nfh_len, stateidp->seqid);
		if ((dp->nfsdi_flags & NFSDI_TIGHTCOUPLED) == 0) {
			tcred = NFSNEWCRED(cred);
			tcred->cr_uid = flp->nfsfl_ffm[mirror].user;
			tcred->cr_groups[0] = flp->nfsfl_ffm[mirror].group;
			tcred->cr_ngroups = 1;
		} else
			tcred = cred;
		if (rwflag == NFSV4OPEN_ACCESSREAD)
			transfer = dp->nfsdi_rsize;
		else
			transfer = dp->nfsdi_wsize;
		NFSLOCKNODE(np);
		np->n_flag |= NDSCOMMIT;
		NFSUNLOCKNODE(np);
		if (len > transfer && docommit == 0)
			xfer = transfer;
		else
			xfer = len;
		if (docommit != 0) {
			if (error == 0) {
				/*
				 * Do last mirrored DS commit with this thread.
				 */
				if (mirror < flp->nfsfl_mirrorcnt - 1)
					error = nfsio_commitds(vp, off, xfer,
					    *dspp, fhp, dp->nfsdi_vers,
					    dp->nfsdi_minorvers, drpc, tcred,
					    p);
				else
					error = nfsrpc_commitds(vp, off, xfer,
					    *dspp, fhp, dp->nfsdi_vers,
					    dp->nfsdi_minorvers, tcred, p);
				NFSCL_DEBUG(4, "commitds=%d\n", error);
				if (error != 0 && error != EACCES && error !=
				    ESTALE) {
					NFSCL_DEBUG(4,
					    "DS layreterr for commit\n");
					nfscl_dserr(NFSV4OP_COMMIT, error, dp,
					    lyp, *dspp);
				}
			}
			NFSCL_DEBUG(4, "aft nfsio_commitds=%d\n", error);
			if (error == 0) {
				/*
				 * Set both eof and uio_resid = 0 to end any
				 * loops.
				 */
				*eofp = 1;
				uiop->uio_resid = 0;
			} else {
				NFSLOCKNODE(np);
				np->n_flag &= ~NDSCOMMIT;
				NFSUNLOCKNODE(np);
			}
		} else if (rwflag == NFSV4OPEN_ACCESSREAD) {
			error = nfsrpc_readds(vp, uiop, stateidp, eofp, *dspp,
			    off, xfer, fhp, 1, dp->nfsdi_vers,
			    dp->nfsdi_minorvers, tcred, p);
			NFSCL_DEBUG(4, "readds=%d\n", error);
			if (error != 0 && error != EACCES && error != ESTALE) {
				NFSCL_DEBUG(4, "DS layreterr for read\n");
				nfscl_dserr(NFSV4OP_READ, error, dp, lyp,
				    *dspp);
			}
		} else {
			if (flp->nfsfl_mirrorcnt == 1) {
				error = nfsrpc_writeds(vp, uiop, iomode,
				    must_commit, stateidp, *dspp, off, xfer,
				    fhp, 0, 1, dp->nfsdi_vers,
				    dp->nfsdi_minorvers, tcred, p);
				if (error == 0) {
					NFSLOCKCLSTATE();
					lyp->nfsly_flags |= NFSLY_WRITTEN;
					NFSUNLOCKCLSTATE();
				}
			} else {
				m = nfsm_copym(mp, rel_off, xfer);
				NFSCL_DEBUG(4, "mcopy reloff=%d xfer=%jd\n",
				    rel_off, (uintmax_t)xfer);
				/*
				 * Do last write to a mirrored DS with this
				 * thread.
				 */
				if (mirror < flp->nfsfl_mirrorcnt - 1)
					error = nfsio_writedsmir(vp, iomode,
					    must_commit, stateidp, *dspp, off,
					    xfer, fhp, m, dp->nfsdi_vers,
					    dp->nfsdi_minorvers, drpc, tcred,
					    p);
				else
					error = nfsrpc_writedsmir(vp, iomode,
					    must_commit, stateidp, *dspp, off,
					    xfer, fhp, m, dp->nfsdi_vers,
					    dp->nfsdi_minorvers, tcred, p);
				NFSCL_DEBUG(4, "nfsio_writedsmir=%d\n", error);
				if (error != 0 && error != EACCES && error !=
				    ESTALE) {
					NFSCL_DEBUG(4,
					    "DS layreterr for write\n");
					nfscl_dserr(NFSV4OP_WRITE, error, dp,
					    lyp, *dspp);
				}
			}
		}
		NFSCL_DEBUG(4, "aft read/writeds=%d\n", error);
		if (error == 0) {
			len -= xfer;
			off += xfer;
			rel_off += xfer;
		}
		if ((dp->nfsdi_flags & NFSDI_TIGHTCOUPLED) == 0)
			NFSFREECRED(tcred);
	}
	NFSCL_DEBUG(4, "eo nfscl_dofflayoutio=%d\n", error);
	return (error);
}