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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHERRYPICK ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cherrypick_seterr(git_commit *commit, const char *fmt)
{
	char commit_oidstr[GIT_OID_HEXSZ + 1];

	git_error_set(GIT_ERROR_CHERRYPICK, fmt,
		git_oid_tostr(commit_oidstr, GIT_OID_HEXSZ + 1, git_commit_id(commit)));

	return -1;
}