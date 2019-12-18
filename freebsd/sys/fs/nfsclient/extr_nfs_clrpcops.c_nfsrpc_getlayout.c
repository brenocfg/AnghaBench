#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ucred {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  nm_clp; } ;
struct nfsfh {int /*<<< orphan*/  nfh_len; int /*<<< orphan*/  nfh_fh; } ;
struct nfsclsession {int nfsess_maxcache; } ;
struct TYPE_6__ {int /*<<< orphan*/ * other; scalar_t__ seqid; } ;
struct nfscllayout {TYPE_1__ nfsly_stateid; } ;
struct nfsclflayouthead {int dummy; } ;
struct nfsclflayout {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * other; scalar_t__ seqid; } ;
typedef  TYPE_2__ nfsv4stateid_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LIST_INIT (struct nfsclflayouthead*) ; 
 scalar_t__ NFSHASFLEXFILE (struct nfsmount*) ; 
 int NFSLAYOUT_FLEXFILE ; 
 int NFSLAYOUT_NFSV4_1_FILES ; 
 int NFSX_STATEID ; 
 int NFSX_UNSIGNED ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 struct nfscllayout* nfscl_getlayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsclflayout**,int*) ; 
 int /*<<< orphan*/  nfscl_rellayout (struct nfscllayout*,int) ; 
 struct nfsclsession* nfsmnt_mdssession (struct nfsmount*) ; 
 int nfsrpc_layoutget (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_2__*,int*,struct nfsclflayouthead*,struct ucred*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsrpc_layoutgetres (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,struct nfscllayout**,struct nfsclflayouthead*,int,int,int /*<<< orphan*/ *,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsrpc_getlayout(struct nfsmount *nmp, vnode_t vp, struct nfsfh *nfhp,
    int iomode, uint32_t *notifybitsp, nfsv4stateid_t *stateidp, uint64_t off,
    struct nfscllayout **lypp, struct ucred *cred, NFSPROC_T *p)
{
	struct nfscllayout *lyp;
	struct nfsclflayout *flp;
	struct nfsclflayouthead flh;
	int error = 0, islocked, layoutlen, layouttype, recalled, retonclose;
	nfsv4stateid_t stateid;
	struct nfsclsession *tsep;

	*lypp = NULL;
	if (NFSHASFLEXFILE(nmp))
		layouttype = NFSLAYOUT_FLEXFILE;
	else
		layouttype = NFSLAYOUT_NFSV4_1_FILES;
	/*
	 * If lyp is returned non-NULL, there will be a refcnt (shared lock)
	 * on it, iff flp != NULL or a lock (exclusive lock) on it iff
	 * flp == NULL.
	 */
	lyp = nfscl_getlayout(nmp->nm_clp, nfhp->nfh_fh, nfhp->nfh_len,
	    off, &flp, &recalled);
	islocked = 0;
	if (lyp == NULL || flp == NULL) {
		if (recalled != 0)
			return (EIO);
		LIST_INIT(&flh);
		tsep = nfsmnt_mdssession(nmp);
		layoutlen = tsep->nfsess_maxcache -
		    (NFSX_STATEID + 3 * NFSX_UNSIGNED);
		if (lyp == NULL) {
			stateid.seqid = 0;
			stateid.other[0] = stateidp->other[0];
			stateid.other[1] = stateidp->other[1];
			stateid.other[2] = stateidp->other[2];
			error = nfsrpc_layoutget(nmp, nfhp->nfh_fh,
			    nfhp->nfh_len, iomode, (uint64_t)0, UINT64_MAX,
			    (uint64_t)0, layouttype, layoutlen, &stateid,
			    &retonclose, &flh, cred, p, NULL);
		} else {
			islocked = 1;
			stateid.seqid = lyp->nfsly_stateid.seqid;
			stateid.other[0] = lyp->nfsly_stateid.other[0];
			stateid.other[1] = lyp->nfsly_stateid.other[1];
			stateid.other[2] = lyp->nfsly_stateid.other[2];
			error = nfsrpc_layoutget(nmp, nfhp->nfh_fh,
			    nfhp->nfh_len, iomode, off, UINT64_MAX,
			    (uint64_t)0, layouttype, layoutlen, &stateid,
			    &retonclose, &flh, cred, p, NULL);
		}
		error = nfsrpc_layoutgetres(nmp, vp, nfhp->nfh_fh,
		    nfhp->nfh_len, &stateid, retonclose, notifybitsp, &lyp,
		    &flh, layouttype, error, NULL, cred, p);
		if (error == 0)
			*lypp = lyp;
		else if (islocked != 0)
			nfscl_rellayout(lyp, 1);
	} else
		*lypp = lyp;
	return (error);
}