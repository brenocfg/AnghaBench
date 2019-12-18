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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCAPABLE ; 
#define  NV_TYPE_NUMBER 129 
#define  NV_TYPE_STRING 128 
 int /*<<< orphan*/  grp_allowed_group (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 

__attribute__((used)) static int
grp_allowed_groups(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const char *name, *gname;
	void *cookie;
	gid_t gid;
	int type;

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &type, &cookie)) != NULL) {
		switch (type) {
		case NV_TYPE_NUMBER:
			gid = (gid_t)nvlist_get_number(newlimits, name);
			gname = NULL;
			break;
		case NV_TYPE_STRING:
			gid = (gid_t)-1;
			gname = nvlist_get_string(newlimits, name);
			break;
		default:
			return (EINVAL);
		}
		if (!grp_allowed_group(oldlimits, gname, gid))
			return (ENOTCAPABLE);
	}

	return (0);
}