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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct uio {int uio_iovcnt; int uio_offset; int uio_resid; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsnode {int n_direofoffset; } ;
struct nfsmount {int dummy; } ;
typedef  int /*<<< orphan*/  nfsuint64 ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int DIRBLKSIZ ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NFSERR_BAD_COOKIE ; 
 int /*<<< orphan*/  NFSHASGOTFSINFO (struct nfsmount*) ; 
 scalar_t__ NFSHASNFSV3 (struct nfsmount*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  ncl_dircookie_lock (struct nfsnode*) ; 
 int /*<<< orphan*/  ncl_dircookie_unlock (struct nfsnode*) ; 
 int /*<<< orphan*/  ncl_fsinfo (struct nfsmount*,struct vnode*,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/ * ncl_getcookie (struct nfsnode*,int,int) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_readdir (struct vnode*,struct uio*,int /*<<< orphan*/ *,struct ucred*,struct thread*,struct nfsvattr*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ncl_readdirrpc(struct vnode *vp, struct uio *uiop, struct ucred *cred,
    struct thread *td)
{
	struct nfsvattr nfsva;
	nfsuint64 *cookiep, cookie;
	struct nfsnode *dnp = VTONFS(vp);
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	int error = 0, eof, attrflag;

	KASSERT(uiop->uio_iovcnt == 1 &&
	    (uiop->uio_offset & (DIRBLKSIZ - 1)) == 0 &&
	    (uiop->uio_resid & (DIRBLKSIZ - 1)) == 0,
	    ("nfs readdirrpc bad uio"));

	/*
	 * If there is no cookie, assume directory was stale.
	 */
	ncl_dircookie_lock(dnp);
	cookiep = ncl_getcookie(dnp, uiop->uio_offset, 0);
	if (cookiep) {
		cookie = *cookiep;
		ncl_dircookie_unlock(dnp);
	} else {
		ncl_dircookie_unlock(dnp);		
		return (NFSERR_BAD_COOKIE);
	}

	if (NFSHASNFSV3(nmp) && !NFSHASGOTFSINFO(nmp))
		(void)ncl_fsinfo(nmp, vp, cred, td);

	error = nfsrpc_readdir(vp, uiop, &cookie, cred, td, &nfsva,
	    &attrflag, &eof, NULL);
	if (attrflag)
		(void) nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0, 1);

	if (!error) {
		/*
		 * We are now either at the end of the directory or have filled
		 * the block.
		 */
		if (eof)
			dnp->n_direofoffset = uiop->uio_offset;
		else {
			if (uiop->uio_resid > 0)
				printf("EEK! readdirrpc resid > 0\n");
			ncl_dircookie_lock(dnp);
			cookiep = ncl_getcookie(dnp, uiop->uio_offset, 1);
			*cookiep = cookie;
			ncl_dircookie_unlock(dnp);
		}
	} else if (NFS_ISV4(vp)) {
		error = nfscl_maperr(td, error, (uid_t)0, (gid_t)0);
	}
	return (error);
}