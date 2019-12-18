#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* z_parent; scalar_t__ z_issnap; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_9__ {TYPE_2__* vfs_data; } ;
typedef  TYPE_3__ vfs_t ;
struct TYPE_7__ {int /*<<< orphan*/  z_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_RELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec_32 (int /*<<< orphan*/ *) ; 
 TYPE_3__* rootvfs ; 
 int /*<<< orphan*/  zfs_active_fs_count ; 
 int /*<<< orphan*/  zfsvfs_free (TYPE_2__*) ; 

__attribute__((used)) static void
zfs_freevfs(vfs_t *vfsp)
{
	zfsvfs_t *zfsvfs = vfsp->vfs_data;

#ifdef illumos
	/*
	 * If this is a snapshot, we have an extra VFS_HOLD on our parent
	 * from zfs_mount().  Release it here.  If we came through
	 * zfs_mountroot() instead, we didn't grab an extra hold, so
	 * skip the VFS_RELE for rootvfs.
	 */
	if (zfsvfs->z_issnap && (vfsp != rootvfs))
		VFS_RELE(zfsvfs->z_parent->z_vfs);
#endif

	zfsvfs_free(zfsvfs);

	atomic_dec_32(&zfs_active_fs_count);
}