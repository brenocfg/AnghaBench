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
struct vop_access_args {int a_accmode; struct ucred* a_cred; int /*<<< orphan*/  a_td; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct fuse_data {int dataflags; int /*<<< orphan*/  daemoncred; } ;

/* Variables and functions */
 int EBADF ; 
 int ENXIO ; 
 int FSESS_INITED ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 struct fuse_data* fuse_get_mpdata (int /*<<< orphan*/ ) ; 
 int fuse_internal_access (struct vnode*,int,int /*<<< orphan*/ ,struct ucred*) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 scalar_t__ fuse_match_cred (int /*<<< orphan*/ ,struct ucred*) ; 
 scalar_t__ priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_islnk (struct vnode*) ; 
 scalar_t__ vnode_isvroot (struct vnode*) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_access(struct vop_access_args *ap)
{
	struct vnode *vp = ap->a_vp;
	int accmode = ap->a_accmode;
	struct ucred *cred = ap->a_cred;

	struct fuse_data *data = fuse_get_mpdata(vnode_mount(vp));

	int err;

	if (fuse_isdeadfs(vp)) {
		if (vnode_isvroot(vp)) {
			return 0;
		}
		return ENXIO;
	}
	if (!(data->dataflags & FSESS_INITED)) {
		if (vnode_isvroot(vp)) {
			if (priv_check_cred(cred, PRIV_VFS_ADMIN) ||
			    (fuse_match_cred(data->daemoncred, cred) == 0)) {
				return 0;
			}
		}
		return EBADF;
	}
	if (vnode_islnk(vp)) {
		return 0;
	}

	err = fuse_internal_access(vp, accmode, ap->a_td, ap->a_cred);
	return err;
}