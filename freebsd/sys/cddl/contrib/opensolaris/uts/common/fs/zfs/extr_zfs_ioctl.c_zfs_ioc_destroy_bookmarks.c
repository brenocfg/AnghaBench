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
 int /*<<< orphan*/  EXDEV ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_bookmark_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 scalar_t__ zfs_component_namecheck (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_destroy_bookmarks(const char *poolname, nvlist_t *innvl,
    nvlist_t *outnvl)
{
	int error, poollen;

	poollen = strlen(poolname);
	for (nvpair_t *pair = nvlist_next_nvpair(innvl, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(innvl, pair)) {
		const char *name = nvpair_name(pair);
		const char *cp = strchr(name, '#');

		/*
		 * The bookmark name must contain an #, and the part after it
		 * must contain only valid characters.
		 */
		if (cp == NULL ||
		    zfs_component_namecheck(cp + 1, NULL, NULL) != 0)
			return (SET_ERROR(EINVAL));

		/*
		 * The bookmark must be in the specified pool.
		 */
		if (strncmp(name, poolname, poollen) != 0 ||
		    (name[poollen] != '/' && name[poollen] != '#'))
			return (SET_ERROR(EXDEV));
	}

	error = dsl_bookmark_destroy(innvl, outnvl);
	return (error);
}