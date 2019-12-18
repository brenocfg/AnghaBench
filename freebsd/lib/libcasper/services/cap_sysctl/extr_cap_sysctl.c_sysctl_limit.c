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
 int /*<<< orphan*/ * cnvlist_get_nvlist (void*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  sysctl_allowed (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int sysctl_valid (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
sysctl_limit(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const nvlist_t *nvl;
	const char *name;
	void *cookie;
	int error, type;

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &type, &cookie)) != NULL) {
		if (strcmp(name, "limit") != 0 || type != NV_TYPE_NVLIST)
			return (EINVAL);
		nvl = cnvlist_get_nvlist(cookie);
		error = sysctl_valid(nvl, true);
		if (error != 0)
			return (error);
		if (!sysctl_allowed(oldlimits, nvl))
			return (ENOTCAPABLE);
	}

	return (0);
}