#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* z_ctldir; int /*<<< orphan*/  z_vfs; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct TYPE_7__ {int /*<<< orphan*/  cmtime; int /*<<< orphan*/ * snapdir; } ;
typedef  TYPE_2__ zfsctl_root_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sfs_node_t ;
typedef  int /*<<< orphan*/  crtime ;
struct TYPE_8__ {int /*<<< orphan*/  z_sa_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  SA_ZPL_CRTIME (TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VFS_ROOT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_4__* VTOZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFSCTL_INO_ROOT ; 
 int /*<<< orphan*/  ZFSCTL_INO_SNAPDIR ; 
 int /*<<< orphan*/  ZFS_TIME_DECODE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * sfs_alloc_node (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 

void
zfsctl_create(zfsvfs_t *zfsvfs)
{
	zfsctl_root_t *dot_zfs;
	sfs_node_t *snapdir;
	vnode_t *rvp;
	uint64_t crtime[2];

	ASSERT(zfsvfs->z_ctldir == NULL);

	snapdir = sfs_alloc_node(sizeof(*snapdir), "snapshot", ZFSCTL_INO_ROOT,
	    ZFSCTL_INO_SNAPDIR);
	dot_zfs = (zfsctl_root_t *)sfs_alloc_node(sizeof(*dot_zfs), ".zfs", 0,
	    ZFSCTL_INO_ROOT);
	dot_zfs->snapdir = snapdir;

	VERIFY(VFS_ROOT(zfsvfs->z_vfs, LK_EXCLUSIVE, &rvp) == 0);
	VERIFY(0 == sa_lookup(VTOZ(rvp)->z_sa_hdl, SA_ZPL_CRTIME(zfsvfs),
	    &crtime, sizeof(crtime)));
	ZFS_TIME_DECODE(&dot_zfs->cmtime, crtime);
	vput(rvp);

	zfsvfs->z_ctldir = dot_zfs;
}