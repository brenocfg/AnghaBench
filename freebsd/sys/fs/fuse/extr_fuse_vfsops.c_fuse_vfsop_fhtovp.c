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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct fuse_vnode_data {scalar_t__ generation; } ;
struct fuse_fid {scalar_t__ gen; int /*<<< orphan*/  nid; } ;
struct fid {int dummy; } ;
struct TYPE_2__ {int dataflags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ESTALE ; 
 int FSESS_EXPORT_SUPPORT ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 struct vnode* NULLVP ; 
 int VFS_VGET (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**) ; 
 struct fuse_vnode_data* VTOFUD (struct vnode*) ; 
 int /*<<< orphan*/  curthread ; 
 TYPE_1__* fuse_get_mpdata (struct mount*) ; 
 int /*<<< orphan*/  vnode_create_vobject (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
fuse_vfsop_fhtovp(struct mount *mp, struct fid *fhp, int flags,
	struct vnode **vpp)
{
	struct fuse_fid *ffhp = (struct fuse_fid *)fhp;
	struct fuse_vnode_data *fvdat;
	struct vnode *nvp;
	int error;

	if (!(fuse_get_mpdata(mp)->dataflags & FSESS_EXPORT_SUPPORT))
		return EOPNOTSUPP;

	error = VFS_VGET(mp, ffhp->nid, LK_EXCLUSIVE, &nvp);
	if (error) {
		*vpp = NULLVP;
		return (error);
	}
	fvdat = VTOFUD(nvp);
	if (fvdat->generation != ffhp->gen ) {
		vput(nvp);
		*vpp = NULLVP;
		return (ESTALE);
	}
	*vpp = nvp;
	vnode_create_vobject(*vpp, 0, curthread);
	return (0);
}