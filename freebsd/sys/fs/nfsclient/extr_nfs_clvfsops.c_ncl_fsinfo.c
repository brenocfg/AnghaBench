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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  nm_mtx; } ;
struct nfsfsinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfscl_loadfsinfo (struct nfsmount*,struct nfsfsinfo*) ; 
 int nfsrpc_fsinfo (struct vnode*,struct nfsfsinfo*,struct ucred*,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 

int
ncl_fsinfo(struct nfsmount *nmp, struct vnode *vp, struct ucred *cred,
    struct thread *td)
{
	struct nfsfsinfo fs;
	struct nfsvattr nfsva;
	int error, attrflag;
	
	error = nfsrpc_fsinfo(vp, &fs, cred, td, &nfsva, &attrflag, NULL);
	if (!error) {
		if (attrflag)
			(void) nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0,
			    1);
		mtx_lock(&nmp->nm_mtx);
		nfscl_loadfsinfo(nmp, &fs);
		mtx_unlock(&nmp->nm_mtx);
	}
	return (error);
}