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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  check_removal_cb ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_patch__can_properly_display_the_removal_of_a_file(void)
{
	/*
	* $ git diff 26a125e..735b6a2
	* diff --git a/subdir.txt b/subdir.txt
	* deleted file mode 100644
	* index e8ee89e..0000000
	* --- a/subdir.txt
	* +++ /dev/null
	* @@ -1,2 +0,0 @@
	* -Is it a bird?
	* -Is it a plane?
	*/

	const char *one_sha = "26a125e";
	const char *another_sha = "735b6a2";
	git_tree *one, *another;
	git_diff *diff;

	g_repo = cl_git_sandbox_init("status");

	one = resolve_commit_oid_to_tree(g_repo, one_sha);
	another = resolve_commit_oid_to_tree(g_repo, another_sha);

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, one, another, NULL));

	cl_git_pass(git_diff_print(
		diff, GIT_DIFF_FORMAT_PATCH, check_removal_cb, NULL));

	git_diff_free(diff);

	git_tree_free(another);
	git_tree_free(one);
}