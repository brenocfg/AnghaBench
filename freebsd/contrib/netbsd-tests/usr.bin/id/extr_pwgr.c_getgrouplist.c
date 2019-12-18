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
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 

int
getgrouplist(const char *name, gid_t basegid, gid_t *groups, int *ngroups)
{
	int cnt, ret;

	if (strcmp(name, "root") == 0) {
		if (*ngroups >= 1) {
			groups[0] = basegid;
			cnt = 1;
		}

		ret = (*ngroups >= cnt) ? 0 : -1;
		*ngroups = cnt;
	} else if (strcmp(name, "test") == 0) {
		if (*ngroups >= 1) {
			groups[0] = basegid;
			cnt = 1;
		}

		if (*ngroups >= 2) {
			groups[1] = 0;
			cnt = 2;
		}

		ret = (*ngroups >= cnt) ? 0 : -1;
		*ngroups = cnt;
	} else
		ret = -1;

	return ret;
}