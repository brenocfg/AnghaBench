#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ git_commit_list_node ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int commit_error(git_commit_list_node *commit, const char *msg)
{
	char commit_oid[GIT_OID_HEXSZ + 1];
	git_oid_fmt(commit_oid, &commit->oid);
	commit_oid[GIT_OID_HEXSZ] = '\0';

	git_error_set(GIT_ERROR_ODB, "failed to parse commit %s - %s", commit_oid, msg);

	return -1;
}