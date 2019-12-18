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
struct vop_reclaim_args {int /*<<< orphan*/  a_td; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/ * v_data; } ;
struct nfsnode {int /*<<< orphan*/  n_excl; int /*<<< orphan*/  n_mtx; struct nfsdmap* n_v4; struct nfsdmap* n_fhp; int /*<<< orphan*/ * n_writecred; int /*<<< orphan*/  n_cookies; } ;
struct nfsdmap {int dummy; } ;

/* Variables and functions */
 struct nfsdmap* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfsdmap* LIST_NEXT (struct nfsdmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDIROFF ; 
 int /*<<< orphan*/  M_NFSFH ; 
 int /*<<< orphan*/  M_NFSV4NODE ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 scalar_t__ VDIR ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct nfsdmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncl_releasesillyrename (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndm_list ; 
 int /*<<< orphan*/  newnfsnode_zone ; 
 int /*<<< orphan*/  nfs_reclaim_p (struct vop_reclaim_args*) ; 
 int /*<<< orphan*/  nfscl_reclaimnode (struct vnode*) ; 
 int /*<<< orphan*/  nfsrpc_close (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_hash_remove (struct vnode*) ; 

int
ncl_reclaim(struct vop_reclaim_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct nfsnode *np = VTONFS(vp);
	struct nfsdmap *dp, *dp2;

	/*
	 * If the NLM is running, give it a chance to abort pending
	 * locks.
	 */
	if (nfs_reclaim_p != NULL)
		nfs_reclaim_p(ap);

	NFSLOCKNODE(np);
	ncl_releasesillyrename(vp, ap->a_td);
	NFSUNLOCKNODE(np);

	if (NFS_ISV4(vp) && vp->v_type == VREG)
		/*
		 * We can now safely close any remaining NFSv4 Opens for
		 * this file. Most opens will have already been closed by
		 * ncl_inactive(), but there are cases where it is not
		 * called, so we need to do it again here.
		 */
		(void) nfsrpc_close(vp, 1, ap->a_td);

	vfs_hash_remove(vp);

	/*
	 * Call nfscl_reclaimnode() to save attributes in the delegation,
	 * as required.
	 */
	if (vp->v_type == VREG)
		nfscl_reclaimnode(vp);

	/*
	 * Free up any directory cookie structures and
	 * large file handle structures that might be associated with
	 * this nfs node.
	 */
	if (vp->v_type == VDIR) {
		dp = LIST_FIRST(&np->n_cookies);
		while (dp) {
			dp2 = dp;
			dp = LIST_NEXT(dp, ndm_list);
			free(dp2, M_NFSDIROFF);
		}
	}
	if (np->n_writecred != NULL)
		crfree(np->n_writecred);
	free(np->n_fhp, M_NFSFH);
	if (np->n_v4 != NULL)
		free(np->n_v4, M_NFSV4NODE);
	mtx_destroy(&np->n_mtx);
	lockdestroy(&np->n_excl);
	uma_zfree(newnfsnode_zone, vp->v_data);
	vp->v_data = NULL;
	return (0);
}