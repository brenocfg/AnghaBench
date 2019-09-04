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
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_4__ {char* old_prefix; char* new_prefix; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  check_diff_patches (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_fixture_submod2 () ; 

void test_diff_submodules__submod2_head_to_index(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_tree *head;
	git_diff *diff = NULL;
	static const char *expected[] = {
		"<SKIP>", /* .gitmodules */
		"diff --git a/sm_added_and_uncommited b/sm_added_and_uncommited\nnew file mode 160000\nindex 0000000..4800958\n--- /dev/null\n+++ b/sm_added_and_uncommited\n@@ -0,0 +1 @@\n+Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n", /* sm_added_and_uncommited */
		"<END>"
	};

	g_repo = setup_fixture_submod2();

	cl_git_pass(git_repository_head_tree(&head, g_repo));

	opts.flags = GIT_DIFF_INCLUDE_UNTRACKED;
	opts.old_prefix = "a"; opts.new_prefix = "b";

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, head, NULL, &opts));
	check_diff_patches(diff, expected);
	git_diff_free(diff);

	git_tree_free(head);
}