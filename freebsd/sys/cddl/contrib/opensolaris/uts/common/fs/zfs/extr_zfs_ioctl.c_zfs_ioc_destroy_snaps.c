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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EXDEV ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_destroy_snapshots_nvl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  zfs_unmount_snap (char*) ; 
 int /*<<< orphan*/  zvol_remove_minors (char const*) ; 

__attribute__((used)) static int
zfs_ioc_destroy_snaps(const char *poolname, nvlist_t *innvl, nvlist_t *outnvl)
{
	int error, poollen;
	nvlist_t *snaps;
	nvpair_t *pair;
	boolean_t defer;

	if (nvlist_lookup_nvlist(innvl, "snaps", &snaps) != 0)
		return (SET_ERROR(EINVAL));
	defer = nvlist_exists(innvl, "defer");

	poollen = strlen(poolname);
	for (pair = nvlist_next_nvpair(snaps, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(snaps, pair)) {
		const char *name = nvpair_name(pair);

		/*
		 * The snap must be in the specified pool to prevent the
		 * invalid removal of zvol minors below.
		 */
		if (strncmp(name, poolname, poollen) != 0 ||
		    (name[poollen] != '/' && name[poollen] != '@'))
			return (SET_ERROR(EXDEV));

		zfs_unmount_snap(nvpair_name(pair));
#if defined(__FreeBSD__)
		zvol_remove_minors(name);
#endif
	}

	return (dsl_destroy_snapshots_nvl(snaps, defer, outnvl));
}