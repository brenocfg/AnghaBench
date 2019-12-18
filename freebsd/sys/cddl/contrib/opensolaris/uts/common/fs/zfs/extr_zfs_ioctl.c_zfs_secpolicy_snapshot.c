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
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int zfs_secpolicy_snapshot_perms (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_snapshot(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	nvlist_t *snaps;
	int error;
	nvpair_t *pair;

	if (nvlist_lookup_nvlist(innvl, "snaps", &snaps) != 0)
		return (SET_ERROR(EINVAL));
	for (pair = nvlist_next_nvpair(snaps, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(snaps, pair)) {
		char *name = nvpair_name(pair);
		char *atp = strchr(name, '@');

		if (atp == NULL) {
			error = SET_ERROR(EINVAL);
			break;
		}
		*atp = '\0';
		error = zfs_secpolicy_snapshot_perms(name, cr);
		*atp = '@';
		if (error != 0)
			break;
	}
	return (error);
}