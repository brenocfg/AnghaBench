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
struct nfsvattr {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  NFSFREECRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSPROC_LAYOUTRETURN ; 
 struct ucred* newnfs_getcred () ; 
 int nfsrv_proxyds (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nfsvattr*,int /*<<< orphan*/ *) ; 

int
nfsrv_updatemdsattr(struct vnode *vp, struct nfsvattr *nap, NFSPROC_T *p)
{
	struct ucred *tcred;
	int error;

	/* Do this as root so that it won't fail with EACCES. */
	tcred = newnfs_getcred();
	error = nfsrv_proxyds(vp, 0, 0, tcred, p, NFSPROC_LAYOUTRETURN,
	    NULL, NULL, NULL, nap, NULL);
	NFSFREECRED(tcred);
	return (error);
}