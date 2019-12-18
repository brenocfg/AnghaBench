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
struct uio {int dummy; } ;
struct mount {int dummy; } ;
struct fuse_notify_inval_inode_out {scalar_t__ ino; scalar_t__ off; } ;
typedef  int /*<<< orphan*/  fniio ;

/* Variables and functions */
 scalar_t__ FUSE_ROOT_ID ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int VFS_ROOT (struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  curthread ; 
 int fuse_internal_get_cached_vnode (struct mount*,scalar_t__,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  fuse_io_invalbuf (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_vnode_clear_attr_cache (struct vnode*) ; 
 int uiomove (struct fuse_notify_inval_inode_out*,int,struct uio*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
fuse_internal_invalidate_inode(struct mount *mp, struct uio *uio)
{
	struct fuse_notify_inval_inode_out fniio;
	struct vnode *vp;
	int err;

	if ((err = uiomove(&fniio, sizeof(fniio), uio)) != 0)
		return (err);

	if (fniio.ino == FUSE_ROOT_ID)
		err = VFS_ROOT(mp, LK_EXCLUSIVE, &vp);
	else
		err = fuse_internal_get_cached_vnode(mp, fniio.ino, LK_SHARED,
			&vp);
	if (err != 0 || vp == NULL)
		return (err);
	/*
	 * XXX we can't check vp's generation because the FUSE invalidate
	 * entry message doesn't include it.  Worse case is that we invalidate
	 * an inode that didn't need to be invalidated.
	 */

	/* 
	 * Flush and invalidate buffers if off >= 0.  Technically we only need
	 * to flush and invalidate the range of offsets [off, off + len), but
	 * for simplicity's sake we do everything.
	 */
	if (fniio.off >= 0)
		fuse_io_invalbuf(vp, curthread);
	fuse_vnode_clear_attr_cache(vp);
	vput(vp);
	return (0);
}