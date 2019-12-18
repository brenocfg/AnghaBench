#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ z_is_sa; int /*<<< orphan*/  z_zfsvfs; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_6__ {int z_acl_version; } ;
typedef  TYPE_2__ zfs_acl_phys_t ;
typedef  int /*<<< orphan*/  acl_phys ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SA_ZPL_ZNODE_ACL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_ACL_VERSION_FUID ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

int
zfs_znode_acl_version(znode_t *zp)
{
	zfs_acl_phys_t acl_phys;

	if (zp->z_is_sa)
		return (ZFS_ACL_VERSION_FUID);
	else {
		int error;

		/*
		 * Need to deal with a potential
		 * race where zfs_sa_upgrade could cause
		 * z_isa_sa to change.
		 *
		 * If the lookup fails then the state of z_is_sa should have
		 * changed.
		 */
		if ((error = sa_lookup(zp->z_sa_hdl,
		    SA_ZPL_ZNODE_ACL(zp->z_zfsvfs),
		    &acl_phys, sizeof (acl_phys))) == 0)
			return (acl_phys.z_acl_version);
		else {
			/*
			 * After upgrade SA_ZPL_ZNODE_ACL should have
			 * been removed.
			 */
			VERIFY(zp->z_is_sa && error == ENOENT);
			return (ZFS_ACL_VERSION_FUID);
		}
	}
}