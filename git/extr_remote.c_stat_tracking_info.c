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
struct branch {int /*<<< orphan*/  refname; } ;
typedef  enum ahead_behind_flags { ____Placeholder_ahead_behind_flags } ahead_behind_flags ;

/* Variables and functions */
 char* branch_get_push (struct branch*,int /*<<< orphan*/ *) ; 
 char* branch_get_upstream (struct branch*,int /*<<< orphan*/ *) ; 
 int stat_branch_pair (int /*<<< orphan*/ ,char const*,int*,int*,int) ; 

int stat_tracking_info(struct branch *branch, int *num_ours, int *num_theirs,
		       const char **tracking_name, int for_push,
		       enum ahead_behind_flags abf)
{
	const char *base;

	/* Cannot stat unless we are marked to build on top of somebody else. */
	base = for_push ? branch_get_push(branch, NULL) :
		branch_get_upstream(branch, NULL);
	if (tracking_name)
		*tracking_name = base;
	if (!base)
		return -1;

	return stat_branch_pair(branch->refname, base, num_ours, num_theirs, abf);
}