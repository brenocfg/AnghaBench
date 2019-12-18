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
 int NV_TYPE_NUMBER ; 
 int NV_TYPE_STRING ; 
 int /*<<< orphan*/  dns_allowed_family (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  dns_allowed_type (int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ limit_has_entry (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
dns_limit(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const char *name;
	void *cookie;
	int nvtype;
	bool hastype, hasfamily;

	hastype = false;
	hasfamily = false;

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &nvtype, &cookie)) != NULL) {
		if (nvtype == NV_TYPE_STRING) {
			const char *type;

			if (strncmp(name, "type", sizeof("type") - 1) != 0)
				return (EINVAL);
			type = nvlist_get_string(newlimits, name);
			if (strcmp(type, "ADDR2NAME") != 0 &&
			    strcmp(type, "NAME2ADDR") != 0 &&
			    strcmp(type, "ADDR") != 0 &&
			    strcmp(type, "NAME") != 0) {
				return (EINVAL);
			}
			if (!dns_allowed_type(oldlimits, type))
				return (ENOTCAPABLE);
			hastype = true;
		} else if (nvtype == NV_TYPE_NUMBER) {
			int family;

			if (strncmp(name, "family", sizeof("family") - 1) != 0)
				return (EINVAL);
			family = (int)nvlist_get_number(newlimits, name);
			if (!dns_allowed_family(oldlimits, family))
				return (ENOTCAPABLE);
			hasfamily = true;
		} else {
			return (EINVAL);
		}
	}

	/*
	 * If the new limit doesn't mention type or family we have to
	 * check if the current limit does have those. Missing type or
	 * family in the limit means that all types or families are
	 * allowed.
	 */
	if (!hastype) {
		if (limit_has_entry(oldlimits, "type"))
			return (ENOTCAPABLE);
	}
	if (!hasfamily) {
		if (limit_has_entry(oldlimits, "family"))
			return (ENOTCAPABLE);
	}

	return (0);
}