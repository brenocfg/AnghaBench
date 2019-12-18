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
struct vnode {int v_iflag; int /*<<< orphan*/ * v_mountedhere; struct autofs_node* v_data; } ;
struct autofs_node {int an_cached; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEBUG (char*) ; 
 int /*<<< orphan*/  AUTOFS_WARN (char*,int) ; 
 int ENOENT ; 
 int LK_RETRY ; 
 int VFS_ROOT (int /*<<< orphan*/ *,int,struct vnode**) ; 
 int VI_DOOMED ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* autofs_softc ; 
 int autofs_trigger (struct autofs_node*,char const*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 
 int /*<<< orphan*/  vunref (struct vnode*) ; 

__attribute__((used)) static int
autofs_trigger_vn(struct vnode *vp, const char *path, int pathlen,
    struct vnode **newvp)
{
	struct autofs_node *anp;
	int error, lock_flags;

	anp = vp->v_data;

	/*
	 * Release the vnode lock, so that other operations, in partcular
	 * mounting a filesystem on top of it, can proceed.  Increase use
	 * count, to prevent the vnode from being deallocated and to prevent
	 * filesystem from being unmounted.
	 */
	lock_flags = VOP_ISLOCKED(vp);
	vref(vp);
	VOP_UNLOCK(vp, 0);

	sx_xlock(&autofs_softc->sc_lock);

	/*
	 * XXX: Workaround for mounting the same thing multiple times; revisit.
	 */
	if (vp->v_mountedhere != NULL) {
		error = 0;
		goto mounted;
	}

	error = autofs_trigger(anp, path, pathlen);
mounted:
	sx_xunlock(&autofs_softc->sc_lock);
	vn_lock(vp, lock_flags | LK_RETRY);
	vunref(vp);
	if ((vp->v_iflag & VI_DOOMED) != 0) {
		AUTOFS_DEBUG("VI_DOOMED");
		return (ENOENT);
	}

	if (error != 0)
		return (error);

	if (vp->v_mountedhere == NULL) {
		*newvp = NULL;
		return (0);
	} else {
		/*
		 * If the operation that succeeded was mount, then mark
		 * the node as non-cached.  Otherwise, if someone unmounts
		 * the filesystem before the cache times out, we will fail
		 * to trigger.
		 */
		anp->an_cached = false;
	}

	error = VFS_ROOT(vp->v_mountedhere, lock_flags, newvp);
	if (error != 0) {
		AUTOFS_WARN("VFS_ROOT() failed with error %d", error);
		return (error);
	}

	return (0);
}