#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* zc_name; int /*<<< orphan*/  zc_value; } ;
typedef  TYPE_3__ zfs_cmd_t ;
struct TYPE_11__ {TYPE_2__* v_vfsp; } ;
typedef  TYPE_4__ vnode_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_8__ {char* f_fstypename; } ;
struct TYPE_9__ {int /*<<< orphan*/  vfs_resource; TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  NO_FOLLOW ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VN_RELE (TYPE_4__*) ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_SHARE ; 
 int dsl_deleg_access (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lookupname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__**) ; 
 scalar_t__ refstr_value (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
zfs_secpolicy_deleg_share(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	vnode_t *vp;
	int error;

	if ((error = lookupname(zc->zc_value, UIO_SYSSPACE,
	    NO_FOLLOW, NULL, &vp)) != 0)
		return (error);

	/* Now make sure mntpnt and dataset are ZFS */

	if (strcmp(vp->v_vfsp->mnt_stat.f_fstypename, "zfs") != 0 ||
	    (strcmp((char *)refstr_value(vp->v_vfsp->vfs_resource),
	    zc->zc_name) != 0)) {
		VN_RELE(vp);
		return (SET_ERROR(EPERM));
	}

	VN_RELE(vp);
	return (dsl_deleg_access(zc->zc_name,
	    ZFS_DELEG_PERM_SHARE, cr));
}