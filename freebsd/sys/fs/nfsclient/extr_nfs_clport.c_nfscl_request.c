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
struct nfsrv_descript {int nd_flag; } ;
struct nfsmount {int /*<<< orphan*/  nm_sockreq; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int ND_NFSV3 ; 
 int ND_NFSV4 ; 
 int /*<<< orphan*/  NFS_PROG ; 
 int NFS_VER2 ; 
 int NFS_VER3 ; 
 int NFS_VER4 ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int newnfs_request (struct nfsrv_descript*,struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ *,struct ucred*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nfscl_request(struct nfsrv_descript *nd, struct vnode *vp, NFSPROC_T *p,
    struct ucred *cred, void *stuff)
{
	int ret, vers;
	struct nfsmount *nmp;

	nmp = VFSTONFS(vp->v_mount);
	if (nd->nd_flag & ND_NFSV4)
		vers = NFS_VER4;
	else if (nd->nd_flag & ND_NFSV3)
		vers = NFS_VER3;
	else
		vers = NFS_VER2;
	ret = newnfs_request(nd, nmp, NULL, &nmp->nm_sockreq, vp, p, cred,
		NFS_PROG, vers, NULL, 1, NULL, NULL);
	return (ret);
}