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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_bookmark_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_bookmark(const char *poolname, nvlist_t *innvl, nvlist_t *outnvl)
{
	for (nvpair_t *pair = nvlist_next_nvpair(innvl, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(innvl, pair)) {
		char *snap_name;

		/*
		 * Verify the snapshot argument.
		 */
		if (nvpair_value_string(pair, &snap_name) != 0)
			return (SET_ERROR(EINVAL));


		/* Verify that the keys (bookmarks) are unique */
		for (nvpair_t *pair2 = nvlist_next_nvpair(innvl, pair);
		    pair2 != NULL; pair2 = nvlist_next_nvpair(innvl, pair2)) {
			if (strcmp(nvpair_name(pair), nvpair_name(pair2)) == 0)
				return (SET_ERROR(EINVAL));
		}
	}

	return (dsl_bookmark_create(innvl, outnvl));
}