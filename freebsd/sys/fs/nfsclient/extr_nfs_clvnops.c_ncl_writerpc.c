#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct vnode {int dummy; } ;
struct uio {int /*<<< orphan*/  uio_td; } ;
struct ucred {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsmount {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {int n_flag; } ;

/* Variables and functions */
 scalar_t__ DOINGASYNC (struct vnode*) ; 
 int EIO ; 
 int ND_NFSV4 ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int) ; 
 scalar_t__ NFSHASPNFS (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSV4OPEN_ACCESSWRITE ; 
 int NFSWRITE_FILESYNC ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 TYPE_1__* VTONFS (struct vnode*) ; 
 int nfscl_doiods (struct vnode*,struct uio*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ) ; 
 int nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_write (struct vnode*,struct uio*,int*,int*,struct ucred*,int /*<<< orphan*/ ,struct nfsvattr*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

int
ncl_writerpc(struct vnode *vp, struct uio *uiop, struct ucred *cred,
    int *iomode, int *must_commit, int called_from_strategy)
{
	struct nfsvattr nfsva;
	int error, attrflag, ret;
	struct nfsmount *nmp;

	nmp = VFSTONFS(vnode_mount(vp));
	error = EIO;
	attrflag = 0;
	if (NFSHASPNFS(nmp))
		error = nfscl_doiods(vp, uiop, iomode, must_commit,
		    NFSV4OPEN_ACCESSWRITE, 0, cred, uiop->uio_td);
	NFSCL_DEBUG(4, "writerpc: aft doiods=%d\n", error);
	if (error != 0)
		error = nfsrpc_write(vp, uiop, iomode, must_commit, cred,
		    uiop->uio_td, &nfsva, &attrflag, NULL,
		    called_from_strategy);
	if (attrflag) {
		if (VTONFS(vp)->n_flag & ND_NFSV4)
			ret = nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 1,
			    1);
		else
			ret = nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0,
			    1);
		if (ret && !error)
			error = ret;
	}
	if (DOINGASYNC(vp))
		*iomode = NFSWRITE_FILESYNC;
	if (error && NFS_ISV4(vp))
		error = nfscl_maperr(uiop->uio_td, error, (uid_t)0, (gid_t)0);
	return (error);
}