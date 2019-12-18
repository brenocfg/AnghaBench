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
typedef  int /*<<< orphan*/  u_quad_t ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct uio {int uio_resid; int /*<<< orphan*/  uio_offset; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsnode {int n_flag; } ;
struct nfsmount {int nm_state; int /*<<< orphan*/  nm_mtx; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EIO ; 
 int NDSCOMMIT ; 
 scalar_t__ NFSHASPNFS (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int NFSSTA_HASWRITEVERF ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSV4OPEN_ACCESSWRITE ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfscl_doiods (struct vnode*,struct uio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_commit (struct vnode*,int /*<<< orphan*/ ,int,struct ucred*,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 

int
ncl_commit(struct vnode *vp, u_quad_t offset, int cnt, struct ucred *cred,
   struct thread *td)
{
	struct nfsvattr nfsva;
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	struct nfsnode *np;
	struct uio uio;
	int error, attrflag;

	np = VTONFS(vp);
	error = EIO;
	attrflag = 0;
	if (NFSHASPNFS(nmp) && (np->n_flag & NDSCOMMIT) != 0) {
		uio.uio_offset = offset;
		uio.uio_resid = cnt;
		error = nfscl_doiods(vp, &uio, NULL, NULL,
		    NFSV4OPEN_ACCESSWRITE, 1, cred, td);
		if (error != 0) {
			NFSLOCKNODE(np);
			np->n_flag &= ~NDSCOMMIT;
			NFSUNLOCKNODE(np);
		}
	}
	if (error != 0) {
		mtx_lock(&nmp->nm_mtx);
		if ((nmp->nm_state & NFSSTA_HASWRITEVERF) == 0) {
			mtx_unlock(&nmp->nm_mtx);
			return (0);
		}
		mtx_unlock(&nmp->nm_mtx);
		error = nfsrpc_commit(vp, offset, cnt, cred, td, &nfsva,
		    &attrflag, NULL);
	}
	if (attrflag != 0)
		(void) nfscl_loadattrcache(&vp, &nfsva, NULL, NULL,
		    0, 1);
	if (error != 0 && NFS_ISV4(vp))
		error = nfscl_maperr(td, error, (uid_t)0, (gid_t)0);
	return (error);
}