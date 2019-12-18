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
struct nfsnode {int n_flag; scalar_t__ n_attrstamp; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int NMODIFIED ; 
 int NREMOVEINPROG ; 
 int NREMOVEWANT ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_remove (struct vnode*,char*,int,struct vnode*,struct ucred*,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_removerpc(struct vnode *dvp, struct vnode *vp, char *name,
    int namelen, struct ucred *cred, struct thread *td)
{
	struct nfsvattr dnfsva;
	struct nfsnode *dnp = VTONFS(dvp);
	int error = 0, dattrflag;

	NFSLOCKNODE(dnp);
	dnp->n_flag |= NREMOVEINPROG;
	NFSUNLOCKNODE(dnp);
	error = nfsrpc_remove(dvp, name, namelen, vp, cred, td, &dnfsva,
	    &dattrflag, NULL);
	NFSLOCKNODE(dnp);
	if ((dnp->n_flag & NREMOVEWANT)) {
		dnp->n_flag &= ~(NREMOVEWANT | NREMOVEINPROG);
		NFSUNLOCKNODE(dnp);
		wakeup((caddr_t)dnp);
	} else {
		dnp->n_flag &= ~NREMOVEINPROG;
		NFSUNLOCKNODE(dnp);
	}
	if (dattrflag)
		(void) nfscl_loadattrcache(&dvp, &dnfsva, NULL, NULL, 0, 1);
	NFSLOCKNODE(dnp);
	dnp->n_flag |= NMODIFIED;
	if (!dattrflag) {
		dnp->n_attrstamp = 0;
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(dvp);
	}
	NFSUNLOCKNODE(dnp);
	if (error && NFS_ISV4(dvp))
		error = nfscl_maperr(td, error, (uid_t)0, (gid_t)0);
	return (error);
}