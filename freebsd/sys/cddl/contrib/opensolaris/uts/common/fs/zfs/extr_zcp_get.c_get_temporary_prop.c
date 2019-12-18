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
struct TYPE_2__ {int /*<<< orphan*/ * z_vfs; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int zfs_prop_t ;
typedef  int /*<<< orphan*/  vfs_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MNTOPT_ATIME ; 
 int /*<<< orphan*/  MNTOPT_DEVICES ; 
 int /*<<< orphan*/  MNTOPT_EXEC ; 
 int /*<<< orphan*/  MNTOPT_NBMAND ; 
 int /*<<< orphan*/  MNTOPT_NOATIME ; 
 int /*<<< orphan*/  MNTOPT_NODEVICES ; 
 int /*<<< orphan*/  MNTOPT_NOEXEC ; 
 int /*<<< orphan*/  MNTOPT_NONBMAND ; 
 int /*<<< orphan*/  MNTOPT_NOSETUID ; 
 int /*<<< orphan*/  MNTOPT_NOXATTR ; 
 int /*<<< orphan*/  MNTOPT_RO ; 
 int /*<<< orphan*/  MNTOPT_RW ; 
 int /*<<< orphan*/  MNTOPT_SETUID ; 
 int /*<<< orphan*/  MNTOPT_XATTR ; 
 int /*<<< orphan*/  VFS_RELE (int /*<<< orphan*/ *) ; 
#define  ZFS_PROP_ATIME 134 
#define  ZFS_PROP_DEVICES 133 
#define  ZFS_PROP_EXEC 132 
#define  ZFS_PROP_NBMAND 131 
#define  ZFS_PROP_READONLY 130 
#define  ZFS_PROP_SETUID 129 
#define  ZFS_PROP_XATTR 128 
 int dmu_objset_from_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int getzfsvfs_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  vfs_optionisset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_rel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_temporary_prop(dsl_dataset_t *ds, zfs_prop_t zfs_prop, uint64_t *val,
    char *setpoint)
{
#ifndef _KERNEL
	return (0);
#else
	int error;
#ifdef illumos
	zfsvfs_t *zfvp;
#endif
	vfs_t *vfsp;
	objset_t *os;
	uint64_t tmp = *val;

	error = dmu_objset_from_ds(ds, &os);
	if (error != 0)
		return (error);

	error = getzfsvfs_impl(os, &vfsp);
	if (error != 0)
		return (error);
#ifdef illumos
	vfsp = zfvp->z_vfs;
#endif
	switch (zfs_prop) {
	case ZFS_PROP_ATIME:
		if (vfs_optionisset(vfsp, MNTOPT_NOATIME, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_ATIME, NULL))
			tmp = 1;
		break;
	case ZFS_PROP_DEVICES:
		if (vfs_optionisset(vfsp, MNTOPT_NODEVICES, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_DEVICES, NULL))
			tmp = 1;
		break;
	case ZFS_PROP_EXEC:
		if (vfs_optionisset(vfsp, MNTOPT_NOEXEC, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_EXEC, NULL))
			tmp = 1;
		break;
	case ZFS_PROP_SETUID:
		if (vfs_optionisset(vfsp, MNTOPT_NOSETUID, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_SETUID, NULL))
			tmp = 1;
		break;
	case ZFS_PROP_READONLY:
		if (vfs_optionisset(vfsp, MNTOPT_RW, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_RO, NULL))
			tmp = 1;
		break;
	case ZFS_PROP_XATTR:
		if (vfs_optionisset(vfsp, MNTOPT_NOXATTR, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_XATTR, NULL))
			tmp = 1;
		break;
	case ZFS_PROP_NBMAND:
		if (vfs_optionisset(vfsp, MNTOPT_NONBMAND, NULL))
			tmp = 0;
		if (vfs_optionisset(vfsp, MNTOPT_NBMAND, NULL))
			tmp = 1;
		break;
	default:
#ifdef illumos
		VFS_RELE(vfsp);
#else
		vfs_rel(vfsp);
#endif
		return (ENOENT);
	}

#ifdef illumos
	VFS_RELE(vfsp);
#else
	vfs_rel(vfsp);
#endif
	if (tmp != *val) {
		(void) strcpy(setpoint, "temporary");
		*val = tmp;
	}
	return (0);
#endif
}