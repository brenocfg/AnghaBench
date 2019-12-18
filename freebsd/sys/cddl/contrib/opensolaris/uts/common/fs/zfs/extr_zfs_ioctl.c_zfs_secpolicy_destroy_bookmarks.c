#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_DESTROY ; 
 int /*<<< orphan*/  fnvlist_remove_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int zfs_secpolicy_write_perms (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_destroy_bookmarks(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	nvpair_t *pair, *nextpair;
	int error = 0;

	for (pair = nvlist_next_nvpair(innvl, NULL); pair != NULL;
	    pair = nextpair) {
		char *name = nvpair_name(pair);
		char *hashp = strchr(name, '#');
		nextpair = nvlist_next_nvpair(innvl, pair);

		if (hashp == NULL) {
			error = SET_ERROR(EINVAL);
			break;
		}

		*hashp = '\0';
		error = zfs_secpolicy_write_perms(name,
		    ZFS_DELEG_PERM_DESTROY, cr);
		*hashp = '#';
		if (error == ENOENT) {
			/*
			 * Ignore any filesystems that don't exist (we consider
			 * their bookmarks "already destroyed").  Remove
			 * the name from the nvl here in case the filesystem
			 * is created between now and when we try to destroy
			 * the bookmark (in which case we don't want to
			 * destroy it since we haven't checked for permission).
			 */
			fnvlist_remove_nvpair(innvl, pair);
			error = 0;
		}
		if (error != 0)
			break;
	}

	return (error);
}