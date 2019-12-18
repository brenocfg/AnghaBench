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
struct group {scalar_t__ gr_gid; scalar_t__* gr_mem; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  endgrent () ; 
 struct group* getgrent () ; 
 int /*<<< orphan*/  setgrent () ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

int
getgrouplist(const char *uname, gid_t agroup, gid_t *groups, int *grpcnt)
{
	struct group *grp;
	int i, ngroups;
	int ret, maxgroups;
	int bail;

	ret = 0;
	ngroups = 0;
	maxgroups = *grpcnt;

	/*
	 * install primary group
	 */
	if (ngroups >= maxgroups) {
		*grpcnt = ngroups;
		return (-1);
	}
	groups[ngroups++] = agroup;

	/*
	 * Scan the group file to find additional groups.
	 */
	setgrent();
	while ((grp = getgrent())) {
		if (grp->gr_gid == agroup)
			continue;
		for (bail = 0, i = 0; bail == 0 && i < ngroups; i++)
			if (groups[i] == grp->gr_gid)
				bail = 1;
		if (bail)
			continue;
		for (i = 0; grp->gr_mem[i]; i++) {
			if (!strcmp(grp->gr_mem[i], uname)) {
				if (ngroups >= maxgroups) {
					ret = -1;
					goto out;
				}
				groups[ngroups++] = grp->gr_gid;
				break;
			}
		}
	}
out:
	endgrent();
	*grpcnt = ngroups;
	return (ret);
}