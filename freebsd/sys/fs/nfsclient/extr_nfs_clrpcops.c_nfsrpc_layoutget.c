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
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int dummy; } ;
struct nfsrv_descript {int nd_repstat; int /*<<< orphan*/  nd_mrep; int /*<<< orphan*/  nd_flag; } ;
struct nfsmount {int /*<<< orphan*/  nm_sockreq; } ;
struct nfsclflayouthead {int dummy; } ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  ND_USEGSSNAME ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int,int) ; 
 int /*<<< orphan*/  NFSPROC_LAYOUTGET ; 
 int /*<<< orphan*/  NFS_PROG ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int newnfs_request (struct nfsrv_descript*,struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfscl_reqstart (struct nfsrv_descript*,int /*<<< orphan*/ ,struct nfsmount*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrv_parselayoutget (struct nfsrv_descript*,int /*<<< orphan*/ *,int*,struct nfsclflayouthead*) ; 
 int /*<<< orphan*/  nfsrv_setuplayoutget (struct nfsrv_descript*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsrpc_layoutget(struct nfsmount *nmp, uint8_t *fhp, int fhlen, int iomode,
    uint64_t offset, uint64_t len, uint64_t minlen, int layouttype,
    int layoutlen, nfsv4stateid_t *stateidp, int *retonclosep,
    struct nfsclflayouthead *flhp, struct ucred *cred, NFSPROC_T *p,
    void *stuff)
{
	struct nfsrv_descript nfsd, *nd = &nfsd;
	int error;

	nfscl_reqstart(nd, NFSPROC_LAYOUTGET, nmp, fhp, fhlen, NULL, NULL, 0,
	    0);
	nfsrv_setuplayoutget(nd, iomode, offset, len, minlen, stateidp,
	    layouttype, layoutlen, 0);
	nd->nd_flag |= ND_USEGSSNAME;
	error = newnfs_request(nd, nmp, NULL, &nmp->nm_sockreq, NULL, p, cred,
	    NFS_PROG, NFS_VER4, NULL, 1, NULL, NULL);
	NFSCL_DEBUG(4, "layget err=%d st=%d\n", error, nd->nd_repstat);
	if (error != 0)
		return (error);
	if (nd->nd_repstat == 0)
		error = nfsrv_parselayoutget(nd, stateidp, retonclosep, flhp);
	if (error == 0 && nd->nd_repstat != 0)
		error = nd->nd_repstat;
	mbuf_freem(nd->nd_mrep);
	return (error);
}