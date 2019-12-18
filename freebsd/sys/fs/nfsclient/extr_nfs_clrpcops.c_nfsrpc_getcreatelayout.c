#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct vattr {int dummy; } ;
struct ucred {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsmount {int dummy; } ;
struct nfsfh {int /*<<< orphan*/  nfh_len; int /*<<< orphan*/ * nfh_fh; } ;
struct nfsclsession {int nfsess_maxcache; } ;
struct nfsclowner {int dummy; } ;
struct nfscllayout {int dummy; } ;
struct nfsclflayouthead {int dummy; } ;
struct nfscldeleg {int dummy; } ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
typedef  int /*<<< orphan*/  nfsquad_t ;
struct TYPE_5__ {int /*<<< orphan*/  v_mount; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (struct nfsclflayouthead*) ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int,int) ; 
 scalar_t__ NFSHASFLEXFILE (struct nfsmount*) ; 
 int NFSLAYOUT_FLEXFILE ; 
 int NFSLAYOUT_NFSV4_1_FILES ; 
 int NFSX_STATEID ; 
 int NFSX_UNSIGNED ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_rellayout (struct nfscllayout*,int /*<<< orphan*/ ) ; 
 struct nfsclsession* nfsmnt_mdssession (struct nfsmount*) ; 
 int nfsrpc_createlayout (TYPE_1__*,char*,int,struct vattr*,int /*<<< orphan*/ ,int,struct nfsclowner*,struct nfscldeleg**,struct ucred*,int /*<<< orphan*/ *,struct nfsvattr*,struct nfsvattr*,struct nfsfh**,int*,int*,void*,int*,int /*<<< orphan*/ *,int,int,int,int*,struct nfsclflayouthead*,int*) ; 
 int nfsrpc_layoutgetres (struct nfsmount*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct nfscllayout**,struct nfsclflayouthead*,int,int,int /*<<< orphan*/ *,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsrpc_getcreatelayout(vnode_t dvp, char *name, int namelen, struct vattr *vap,
    nfsquad_t cverf, int fmode, struct nfsclowner *owp, struct nfscldeleg **dpp,
    struct ucred *cred, NFSPROC_T *p, struct nfsvattr *dnap,
    struct nfsvattr *nnap, struct nfsfh **nfhpp, int *attrflagp,
    int *dattrflagp, void *dstuff, int *unlockedp)
{
	struct nfscllayout *lyp;
	struct nfsclflayouthead flh;
	struct nfsfh *nfhp;
	struct nfsclsession *tsep;
	struct nfsmount *nmp;
	nfsv4stateid_t stateid;
	int error, layoutlen, layouttype, retonclose, laystat;

	error = 0;
	nmp = VFSTONFS(dvp->v_mount);
	if (NFSHASFLEXFILE(nmp))
		layouttype = NFSLAYOUT_FLEXFILE;
	else
		layouttype = NFSLAYOUT_NFSV4_1_FILES;
	LIST_INIT(&flh);
	tsep = nfsmnt_mdssession(nmp);
	layoutlen = tsep->nfsess_maxcache - (NFSX_STATEID + 3 * NFSX_UNSIGNED);
	error = nfsrpc_createlayout(dvp, name, namelen, vap, cverf, fmode,
	    owp, dpp, cred, p, dnap, nnap, nfhpp, attrflagp, dattrflagp,
	    dstuff, unlockedp, &stateid, 1, layouttype, layoutlen, &retonclose,
	    &flh, &laystat);
	NFSCL_DEBUG(4, "aft nfsrpc_createlayoutrpc laystat=%d err=%d\n",
	    laystat, error);
	lyp = NULL;
	if (laystat == 0) {
		nfhp = *nfhpp;
		laystat = nfsrpc_layoutgetres(nmp, dvp, nfhp->nfh_fh,
		    nfhp->nfh_len, &stateid, retonclose, NULL, &lyp, &flh,
		    layouttype, laystat, NULL, cred, p);
	} else
		laystat = nfsrpc_layoutgetres(nmp, dvp, NULL, 0, &stateid,
		    retonclose, NULL, &lyp, &flh, layouttype, laystat, NULL,
		    cred, p);
	if (laystat == 0)
		nfscl_rellayout(lyp, 0);
	return (error);
}