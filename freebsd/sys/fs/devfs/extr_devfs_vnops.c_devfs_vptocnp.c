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
struct vop_vptocnp_args {char* a_buf; int* a_buflen; struct vnode** a_vpp; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct devfs_dirent* v_data; int /*<<< orphan*/  v_mount; } ;
struct devfs_mount {int /*<<< orphan*/  dm_lock; struct devfs_dirent* dm_rootdir; } ;
struct devfs_dirent {struct vnode* de_vnode; TYPE_1__* de_dirent; } ;
struct TYPE_2__ {scalar_t__ d_namlen; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ VCHR ; 
 scalar_t__ VDIR ; 
 struct devfs_mount* VFSTODEVFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  devfs_de_interlock ; 
 struct devfs_dirent* devfs_parent_dirent (struct devfs_dirent*) ; 
 int devfs_populate_vp (struct vnode*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vholdl (struct vnode*) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 

__attribute__((used)) static int
devfs_vptocnp(struct vop_vptocnp_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode **dvp = ap->a_vpp;
	struct devfs_mount *dmp;
	char *buf = ap->a_buf;
	int *buflen = ap->a_buflen;
	struct devfs_dirent *dd, *de;
	int i, error;

	dmp = VFSTODEVFS(vp->v_mount);

	error = devfs_populate_vp(vp);
	if (error != 0)
		return (error);

	if (vp->v_type != VCHR && vp->v_type != VDIR) {
		error = ENOENT;
		goto finished;
	}

	dd = vp->v_data;
	if (vp->v_type == VDIR && dd == dmp->dm_rootdir) {
		*dvp = vp;
		vref(*dvp);
		goto finished;
	}

	i = *buflen;
	i -= dd->de_dirent->d_namlen;
	if (i < 0) {
		error = ENOMEM;
		goto finished;
	}
	bcopy(dd->de_dirent->d_name, buf + i, dd->de_dirent->d_namlen);
	*buflen = i;
	de = devfs_parent_dirent(dd);
	if (de == NULL) {
		error = ENOENT;
		goto finished;
	}
	mtx_lock(&devfs_de_interlock);
	*dvp = de->de_vnode;
	if (*dvp != NULL) {
		VI_LOCK(*dvp);
		mtx_unlock(&devfs_de_interlock);
		vholdl(*dvp);
		VI_UNLOCK(*dvp);
		vref(*dvp);
		vdrop(*dvp);
	} else {
		mtx_unlock(&devfs_de_interlock);
		error = ENOENT;
	}
finished:
	sx_xunlock(&dmp->dm_lock);
	return (error);
}