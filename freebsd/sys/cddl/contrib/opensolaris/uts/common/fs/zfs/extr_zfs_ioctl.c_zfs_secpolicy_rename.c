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
struct TYPE_3__ {int zc_cookie; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_BOOKMARK ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_RENAME ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int zfs_secpolicy_rename_perms (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_write_perms (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_rename(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	char *at = NULL;
	char *pound;
	int error;

	if ((pound = strchr(zc->zc_name, '#')) != NULL) {
		*pound = '\0';
		error = zfs_secpolicy_write_perms(zc->zc_name,
		    ZFS_DELEG_PERM_RENAME, cr);
		if (error == 0) {
			error = zfs_secpolicy_write_perms(zc->zc_name,
			    ZFS_DELEG_PERM_BOOKMARK, cr);
		}
		*pound = '#';
		return (error);
	}

	if ((zc->zc_cookie & 1) != 0) {
		/*
		 * This is recursive rename, so the starting snapshot might
		 * not exist. Check file system or volume permission instead.
		 */
		at = strchr(zc->zc_name, '@');
		if (at == NULL)
			return (EINVAL);
		*at = '\0';
	}

	error = zfs_secpolicy_rename_perms(zc->zc_name, zc->zc_value, cr);

	if (at != NULL)
		*at = '@';

	return (error);
}