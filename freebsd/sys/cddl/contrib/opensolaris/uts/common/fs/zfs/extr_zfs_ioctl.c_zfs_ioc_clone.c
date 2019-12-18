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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 scalar_t__ dataset_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_objset_clone (char const*,char*) ; 
 int /*<<< orphan*/  dsl_destroy_head (char const*) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ strchr (char const*,char) ; 
 int zfs_set_prop_nvlist (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_create_minors (char const*) ; 

__attribute__((used)) static int
zfs_ioc_clone(const char *fsname, nvlist_t *innvl, nvlist_t *outnvl)
{
	int error = 0;
	nvlist_t *nvprops = NULL;
	char *origin_name;

	if (nvlist_lookup_string(innvl, "origin", &origin_name) != 0)
		return (SET_ERROR(EINVAL));
	(void) nvlist_lookup_nvlist(innvl, "props", &nvprops);

	if (strchr(fsname, '@') ||
	    strchr(fsname, '%'))
		return (SET_ERROR(EINVAL));

	if (dataset_namecheck(origin_name, NULL, NULL) != 0)
		return (SET_ERROR(EINVAL));
	error = dmu_objset_clone(fsname, origin_name);
	if (error != 0)
		return (error);

	/*
	 * It would be nice to do this atomically.
	 */
	if (error == 0) {
		error = zfs_set_prop_nvlist(fsname, ZPROP_SRC_LOCAL,
		    nvprops, outnvl);
		if (error != 0)
			(void) dsl_destroy_head(fsname);
	}
#ifdef __FreeBSD__
	if (error == 0)
		zvol_create_minors(fsname);
#endif
	return (error);
}