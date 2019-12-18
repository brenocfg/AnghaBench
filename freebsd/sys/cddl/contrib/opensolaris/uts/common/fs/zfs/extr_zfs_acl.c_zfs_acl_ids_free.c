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
struct TYPE_3__ {int /*<<< orphan*/ * z_fuidp; int /*<<< orphan*/ * z_aclp; } ;
typedef  TYPE_1__ zfs_acl_ids_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_info_free (int /*<<< orphan*/ *) ; 

void
zfs_acl_ids_free(zfs_acl_ids_t *acl_ids)
{
	if (acl_ids->z_aclp)
		zfs_acl_free(acl_ids->z_aclp);
	if (acl_ids->z_fuidp)
		zfs_fuid_info_free(acl_ids->z_fuidp);
	acl_ids->z_aclp = NULL;
	acl_ids->z_fuidp = NULL;
}