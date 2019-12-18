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
struct vnode {int dummy; } ;
struct vattr {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsnode {int /*<<< orphan*/  n_flag; TYPE_1__* n_accesscache; } ;
struct TYPE_2__ {scalar_t__ stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ACCESSCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NDELEGMOD ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFS_ACCESSCACHESIZE ; 
 scalar_t__ NFS_ISV34 (struct vnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_setattr (struct vnode*,struct vattr*,int /*<<< orphan*/ *,struct ucred*,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_setattrrpc(struct vnode *vp, struct vattr *vap, struct ucred *cred,
    struct thread *td)
{
	struct nfsnode *np = VTONFS(vp);
	int error, ret, attrflag, i;
	struct nfsvattr nfsva;

	if (NFS_ISV34(vp)) {
		NFSLOCKNODE(np);
		for (i = 0; i < NFS_ACCESSCACHESIZE; i++)
			np->n_accesscache[i].stamp = 0;
		np->n_flag |= NDELEGMOD;
		NFSUNLOCKNODE(np);
		KDTRACE_NFS_ACCESSCACHE_FLUSH_DONE(vp);
	}
	error = nfsrpc_setattr(vp, vap, NULL, cred, td, &nfsva, &attrflag,
	    NULL);
	if (attrflag) {
		ret = nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0, 1);
		if (ret && !error)
			error = ret;
	}
	if (error && NFS_ISV4(vp))
		error = nfscl_maperr(td, error, vap->va_uid, vap->va_gid);
	return (error);
}