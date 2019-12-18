#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  z_os; int /*<<< orphan*/  z_version; int /*<<< orphan*/  z_use_sa; scalar_t__ z_vfs; scalar_t__ z_use_fuids; } ;
typedef  TYPE_1__ zfsvfs_t ;

/* Variables and functions */
 scalar_t__ USE_FUIDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE_SA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFSFT_ACCESS_FILTER ; 
 int /*<<< orphan*/  VFSFT_ACEMASKONACCESS ; 
 int /*<<< orphan*/  VFSFT_ACLONCREATE ; 
 int /*<<< orphan*/  VFSFT_REPARSE ; 
 int /*<<< orphan*/  VFSFT_SYSATTR_VIEWS ; 
 int /*<<< orphan*/  VFSFT_XVATTR ; 
 int /*<<< orphan*/  vfs_clear_feature (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_set_feature (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zfs_set_fuid_feature(zfsvfs_t *zfsvfs)
{
	zfsvfs->z_use_fuids = USE_FUIDS(zfsvfs->z_version, zfsvfs->z_os);
	if (zfsvfs->z_vfs) {
		if (zfsvfs->z_use_fuids) {
			vfs_set_feature(zfsvfs->z_vfs, VFSFT_XVATTR);
			vfs_set_feature(zfsvfs->z_vfs, VFSFT_SYSATTR_VIEWS);
			vfs_set_feature(zfsvfs->z_vfs, VFSFT_ACEMASKONACCESS);
			vfs_set_feature(zfsvfs->z_vfs, VFSFT_ACLONCREATE);
			vfs_set_feature(zfsvfs->z_vfs, VFSFT_ACCESS_FILTER);
			vfs_set_feature(zfsvfs->z_vfs, VFSFT_REPARSE);
		} else {
			vfs_clear_feature(zfsvfs->z_vfs, VFSFT_XVATTR);
			vfs_clear_feature(zfsvfs->z_vfs, VFSFT_SYSATTR_VIEWS);
			vfs_clear_feature(zfsvfs->z_vfs, VFSFT_ACEMASKONACCESS);
			vfs_clear_feature(zfsvfs->z_vfs, VFSFT_ACLONCREATE);
			vfs_clear_feature(zfsvfs->z_vfs, VFSFT_ACCESS_FILTER);
			vfs_clear_feature(zfsvfs->z_vfs, VFSFT_REPARSE);
		}
	}
	zfsvfs->z_use_sa = USE_SA(zfsvfs->z_version, zfsvfs->z_os);
}