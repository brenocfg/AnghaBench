#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
struct TYPE_7__ {int /*<<< orphan*/  z_root; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
struct TYPE_8__ {TYPE_1__* vfs_data; } ;
typedef  TYPE_2__ vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  VN_RELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 int /*<<< orphan*/ * ZTOV (int /*<<< orphan*/ *) ; 
 int vn_lock (int /*<<< orphan*/ *,int) ; 
 int zfs_zget (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
zfs_root(vfs_t *vfsp, int flags, vnode_t **vpp)
{
	zfsvfs_t *zfsvfs = vfsp->vfs_data;
	znode_t *rootzp;
	int error;

	ZFS_ENTER(zfsvfs);

	error = zfs_zget(zfsvfs, zfsvfs->z_root, &rootzp);
	if (error == 0)
		*vpp = ZTOV(rootzp);

	ZFS_EXIT(zfsvfs);

	if (error == 0) {
		error = vn_lock(*vpp, flags);
		if (error != 0) {
			VN_RELE(*vpp);
			*vpp = NULL;
		}
	}
	return (error);
}