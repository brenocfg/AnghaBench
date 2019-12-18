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
struct vop_inactive_args {int /*<<< orphan*/  a_td; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/ * v_object; } ;
struct nfsnode {int n_flag; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_WAIT ; 
 int NDSCOMMIT ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int NMODIFIED ; 
 int /*<<< orphan*/  OBJPC_SYNC ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  ncl_flush (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_releasesillyrename (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrpc_close (struct vnode*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_page_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ncl_inactive(struct vop_inactive_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct nfsnode *np;
	boolean_t retv;

	if (NFS_ISV4(vp) && vp->v_type == VREG) {
		/*
		 * Since mmap()'d files do I/O after VOP_CLOSE(), the NFSv4
		 * Close operations are delayed until now. Any dirty
		 * buffers/pages must be flushed before the close, so that the
		 * stateid is available for the writes.
		 */
		if (vp->v_object != NULL) {
			VM_OBJECT_WLOCK(vp->v_object);
			retv = vm_object_page_clean(vp->v_object, 0, 0,
			    OBJPC_SYNC);
			VM_OBJECT_WUNLOCK(vp->v_object);
		} else
			retv = TRUE;
		if (retv == TRUE) {
			(void)ncl_flush(vp, MNT_WAIT, ap->a_td, 1, 0);
			(void)nfsrpc_close(vp, 1, ap->a_td);
		}
	}

	np = VTONFS(vp);
	NFSLOCKNODE(np);
	ncl_releasesillyrename(vp, ap->a_td);

	/*
	 * NMODIFIED means that there might be dirty/stale buffers
	 * associated with the NFS vnode.
	 * NDSCOMMIT means that the file is on a pNFS server and commits
	 * should be done to the DS.
	 * None of the other flags are meaningful after the vnode is unused.
	 */
	np->n_flag &= (NMODIFIED | NDSCOMMIT);
	NFSUNLOCKNODE(np);
	return (0);
}