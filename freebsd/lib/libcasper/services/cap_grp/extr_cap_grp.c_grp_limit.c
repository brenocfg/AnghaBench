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
 int EINVAL ; 
 int ENOTCAPABLE ; 
 int NV_TYPE_NVLIST ; 
 int grp_allowed_cmds (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int grp_allowed_fields (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int grp_allowed_groups (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
grp_limit(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const nvlist_t *limits;
	const char *name;
	void *cookie;
	int error, type;

	if (oldlimits != NULL && nvlist_exists_nvlist(oldlimits, "cmds") &&
	    !nvlist_exists_nvlist(newlimits, "cmds")) {
		return (ENOTCAPABLE);
	}
	if (oldlimits != NULL && nvlist_exists_nvlist(oldlimits, "fields") &&
	    !nvlist_exists_nvlist(newlimits, "fields")) {
		return (ENOTCAPABLE);
	}
	if (oldlimits != NULL && nvlist_exists_nvlist(oldlimits, "groups") &&
	    !nvlist_exists_nvlist(newlimits, "groups")) {
		return (ENOTCAPABLE);
	}

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &type, &cookie)) != NULL) {
		if (type != NV_TYPE_NVLIST)
			return (EINVAL);
		limits = nvlist_get_nvlist(newlimits, name);
		if (strcmp(name, "cmds") == 0)
			error = grp_allowed_cmds(oldlimits, limits);
		else if (strcmp(name, "fields") == 0)
			error = grp_allowed_fields(oldlimits, limits);
		else if (strcmp(name, "groups") == 0)
			error = grp_allowed_groups(oldlimits, limits);
		else
			error = EINVAL;
		if (error != 0)
			return (error);
	}

	return (0);
}