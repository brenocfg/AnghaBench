#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  oldest_commit; } ;
typedef  TYPE_1__ git_blame_options ;

/* Variables and functions */
 TYPE_1__ GIT_BLAME_OPTIONS_INIT ; 
 int /*<<< orphan*/  check_blame_hunk_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_blame ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blame_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_blame_get_hunk_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_blame_simple__can_restrict_to_newish_commits(void)
{
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;

	cl_git_pass(git_repository_open(&g_repo, cl_fixture("testrepo.git")));

	{
		git_object *obj;
		cl_git_pass(git_revparse_single(&obj, g_repo, "be3563a"));
		git_oid_cpy(&opts.oldest_commit, git_object_id(obj));
		git_object_free(obj);
	}

	cl_git_pass(git_blame_file(&g_blame, g_repo, "branch_file.txt", &opts));

	cl_assert_equal_i(2, git_blame_get_hunk_count(g_blame));
	check_blame_hunk_index(g_repo, g_blame, 0,  1, 1, 1, "be3563a", "branch_file.txt");
	check_blame_hunk_index(g_repo, g_blame, 1,  2, 1, 0, "a65fedf", "branch_file.txt");
}