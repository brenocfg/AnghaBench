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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsnode {scalar_t__ n_attrstamp; int /*<<< orphan*/  n_flag; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int /*<<< orphan*/  NMODIFIED ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_rename (struct vnode*,struct vnode*,char*,int,struct vnode*,struct vnode*,char*,int,struct ucred*,struct thread*,struct nfsvattr*,struct nfsvattr*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_renamerpc(struct vnode *fdvp, struct vnode *fvp, char *fnameptr,
    int fnamelen, struct vnode *tdvp, struct vnode *tvp, char *tnameptr,
    int tnamelen, struct ucred *cred, struct thread *td)
{
	struct nfsvattr fnfsva, tnfsva;
	struct nfsnode *fdnp = VTONFS(fdvp);
	struct nfsnode *tdnp = VTONFS(tdvp);
	int error = 0, fattrflag, tattrflag;

	error = nfsrpc_rename(fdvp, fvp, fnameptr, fnamelen, tdvp, tvp,
	    tnameptr, tnamelen, cred, td, &fnfsva, &tnfsva, &fattrflag,
	    &tattrflag, NULL, NULL);
	NFSLOCKNODE(fdnp);
	fdnp->n_flag |= NMODIFIED;
	if (fattrflag != 0) {
		NFSUNLOCKNODE(fdnp);
		(void) nfscl_loadattrcache(&fdvp, &fnfsva, NULL, NULL, 0, 1);
	} else {
		fdnp->n_attrstamp = 0;
		NFSUNLOCKNODE(fdnp);
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(fdvp);
	}
	NFSLOCKNODE(tdnp);
	tdnp->n_flag |= NMODIFIED;
	if (tattrflag != 0) {
		NFSUNLOCKNODE(tdnp);
		(void) nfscl_loadattrcache(&tdvp, &tnfsva, NULL, NULL, 0, 1);
	} else {
		tdnp->n_attrstamp = 0;
		NFSUNLOCKNODE(tdnp);
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(tdvp);
	}
	if (error && NFS_ISV4(fdvp))
		error = nfscl_maperr(td, error, (uid_t)0, (gid_t)0);
	return (error);
}