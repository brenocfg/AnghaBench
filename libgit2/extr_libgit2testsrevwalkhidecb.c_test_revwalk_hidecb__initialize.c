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

/* Variables and functions */
 int /*<<< orphan*/  _head_id ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int commit_count ; 
 int /*<<< orphan*/  commit_head ; 
 int /*<<< orphan*/ * commit_ids ; 
 int /*<<< orphan*/ * commit_strs ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_revwalk_hidecb__initialize(void)
{
	int i;

	cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	cl_git_pass(git_oid_fromstr(&_head_id, commit_head));

	for (i = 0; i < commit_count; i++)
		cl_git_pass(git_oid_fromstr(&commit_ids[i], commit_strs[i]));

}