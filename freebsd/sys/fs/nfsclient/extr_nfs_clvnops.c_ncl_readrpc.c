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
typedef  int /*<<< orphan*/  uid_t ;
struct vnode {int dummy; } ;
struct uio {int /*<<< orphan*/  uio_td; } ;
struct ucred {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsmount {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int) ; 
 scalar_t__ NFSHASPNFS (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSV4OPEN_ACCESSREAD ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int nfscl_doiods (struct vnode*,struct uio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ) ; 
 int nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_read (struct vnode*,struct uio*,struct ucred*,int /*<<< orphan*/ ,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

int
ncl_readrpc(struct vnode *vp, struct uio *uiop, struct ucred *cred)
{
	int error, ret, attrflag;
	struct nfsvattr nfsva;
	struct nfsmount *nmp;

	nmp = VFSTONFS(vnode_mount(vp));
	error = EIO;
	attrflag = 0;
	if (NFSHASPNFS(nmp))
		error = nfscl_doiods(vp, uiop, NULL, NULL,
		    NFSV4OPEN_ACCESSREAD, 0, cred, uiop->uio_td);
	NFSCL_DEBUG(4, "readrpc: aft doiods=%d\n", error);
	if (error != 0)
		error = nfsrpc_read(vp, uiop, cred, uiop->uio_td, &nfsva,
		    &attrflag, NULL);
	if (attrflag) {
		ret = nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0, 1);
		if (ret && !error)
			error = ret;
	}
	if (error && NFS_ISV4(vp))
		error = nfscl_maperr(uiop->uio_td, error, (uid_t)0, (gid_t)0);
	return (error);
}