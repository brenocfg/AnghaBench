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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
#define  NV_TYPE_NUMBER 129 
#define  NV_TYPE_STRING 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool
grp_allowed_group(const nvlist_t *limits, const char *gname, gid_t gid)
{
	const char *name;
	void *cookie;
	int type;

	if (limits == NULL)
		return (true);

	/*
	 * If no limit was set on allowed groups, then all groups are allowed.
	 */
	if (!nvlist_exists_nvlist(limits, "groups"))
		return (true);

	limits = nvlist_get_nvlist(limits, "groups");
	cookie = NULL;
	while ((name = nvlist_next(limits, &type, &cookie)) != NULL) {
		switch (type) {
		case NV_TYPE_NUMBER:
			if (gid != (gid_t)-1 &&
			    nvlist_get_number(limits, name) == (uint64_t)gid) {
				return (true);
			}
			break;
		case NV_TYPE_STRING:
			if (gname != NULL &&
			    strcmp(nvlist_get_string(limits, name),
			    gname) == 0) {
				return (true);
			}
			break;
		default:
			abort();
		}
	}

	return (false);
}