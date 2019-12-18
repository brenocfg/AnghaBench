#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_vflag; } ;
struct nfsnode {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  nm_mtx; int /*<<< orphan*/  nm_fhsize; int /*<<< orphan*/  nm_fh; } ;
struct mount {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSHASGOTFSINFO (struct nfsmount*) ; 
 scalar_t__ NFSHASNFSV3 (struct nfsmount*) ; 
 struct vnode* NFSTOV (struct nfsnode*) ; 
 scalar_t__ VDIR ; 
 struct nfsmount* VFSTONFS (struct mount*) ; 
 scalar_t__ VNON ; 
 int /*<<< orphan*/  VV_ROOT ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncl_fsinfo (struct nfsmount*,struct vnode*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ncl_nget (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsnode**,int) ; 

__attribute__((used)) static int
nfs_root(struct mount *mp, int flags, struct vnode **vpp)
{
	struct vnode *vp;
	struct nfsmount *nmp;
	struct nfsnode *np;
	int error;

	nmp = VFSTONFS(mp);
	error = ncl_nget(mp, nmp->nm_fh, nmp->nm_fhsize, &np, flags);
	if (error)
		return error;
	vp = NFSTOV(np);
	/*
	 * Get transfer parameters and attributes for root vnode once.
	 */
	mtx_lock(&nmp->nm_mtx);
	if (NFSHASNFSV3(nmp) && !NFSHASGOTFSINFO(nmp)) {
		mtx_unlock(&nmp->nm_mtx);
		ncl_fsinfo(nmp, vp, curthread->td_ucred, curthread);
	} else 
		mtx_unlock(&nmp->nm_mtx);
	if (vp->v_type == VNON)
	    vp->v_type = VDIR;
	vp->v_vflag |= VV_ROOT;
	*vpp = vp;
	return (0);
}