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
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_3__ {int /*<<< orphan*/  z_fgid; int /*<<< orphan*/  z_fuid; } ;
typedef  TYPE_1__ zfs_acl_ids_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ zfs_fuid_overquota (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
zfs_acl_ids_overquota(zfsvfs_t *zfsvfs, zfs_acl_ids_t *acl_ids)
{
	return (zfs_fuid_overquota(zfsvfs, B_FALSE, acl_ids->z_fuid) ||
	    zfs_fuid_overquota(zfsvfs, B_TRUE, acl_ids->z_fgid));
}