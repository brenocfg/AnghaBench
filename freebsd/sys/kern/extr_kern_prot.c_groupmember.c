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
struct ucred {scalar_t__* cr_groups; int cr_ngroups; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */

int
groupmember(gid_t gid, struct ucred *cred)
{
	int l;
	int h;
	int m;

	if (cred->cr_groups[0] == gid)
		return(1);

	/*
	 * If gid was not our primary group, perform a binary search
	 * of the supplemental groups.  This is possible because we
	 * sort the groups in crsetgroups().
	 */
	l = 1;
	h = cred->cr_ngroups;
	while (l < h) {
		m = l + ((h - l) / 2);
		if (cred->cr_groups[m] < gid)
			l = m + 1; 
		else
			h = m; 
	}
	if ((l < cred->cr_ngroups) && (cred->cr_groups[l] == gid))
		return (1);

	return (0);
}