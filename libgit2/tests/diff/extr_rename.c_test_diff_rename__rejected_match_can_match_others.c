#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct rename_expected {int member_0; unsigned int* member_1; char const** member_2; char const** member_3; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_13__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_2__ git_checkout_options ;
struct TYPE_14__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_2__ GIT_CHECKOUT_OPTIONS_INIT ; 
 unsigned int GIT_DELTA_RENAMED ; 
 TYPE_1__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_assert (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rename_expected*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_futils_writebuffer (TYPE_3__*,char*,int,int) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_set_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 char* strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_names_expected ; 

void test_diff_rename__rejected_match_can_match_others(void)
{
	git_reference *head, *selfsimilar;
	git_index *index;
	git_tree *tree;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_diff *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options findopts = GIT_DIFF_FIND_OPTIONS_INIT;
	git_buf one = GIT_BUF_INIT, two = GIT_BUF_INIT;
	unsigned int status[] = { GIT_DELTA_RENAMED, GIT_DELTA_RENAMED };
	const char *sources[] = { "Class1.cs", "Class2.cs" };
	const char *targets[] = { "ClassA.cs", "ClassB.cs" };
	struct rename_expected expect = { 2, status, sources, targets };
	char *ptr;

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	findopts.flags = GIT_DIFF_FIND_RENAMES;

	cl_git_pass(git_reference_lookup(&head, g_repo, "HEAD"));
	cl_git_pass(git_reference_symbolic_set_target(
		&selfsimilar, head, "refs/heads/renames_similar", NULL));
	cl_git_pass(git_checkout_head(g_repo, &opts));
	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_pass(git_futils_readbuffer(&one, "renames/Class1.cs"));
	cl_git_pass(git_futils_readbuffer(&two, "renames/Class2.cs"));

	cl_git_pass(p_unlink("renames/Class1.cs"));
	cl_git_pass(p_unlink("renames/Class2.cs"));

	cl_git_pass(git_index_remove_bypath(index, "Class1.cs"));
	cl_git_pass(git_index_remove_bypath(index, "Class2.cs"));

	cl_assert(ptr = strstr(one.ptr, "Class1"));
	ptr[5] = 'A';

	cl_assert(ptr = strstr(two.ptr, "Class2"));
	ptr[5] = 'B';

	cl_git_pass(
		git_futils_writebuffer(&one, "renames/ClassA.cs", O_RDWR|O_CREAT, 0777));
	cl_git_pass(
		git_futils_writebuffer(&two, "renames/ClassB.cs", O_RDWR|O_CREAT, 0777));

	cl_git_pass(git_index_add_bypath(index, "ClassA.cs"));
	cl_git_pass(git_index_add_bypath(index, "ClassB.cs"));

	cl_git_pass(git_index_write(index));

	cl_git_pass(
		git_revparse_single((git_object **)&tree, g_repo, "HEAD^{tree}"));

	cl_git_pass(
		git_diff_tree_to_index(&diff, g_repo, tree, index, &diffopts));

	cl_git_pass(git_diff_find_similar(diff, &findopts));

	cl_git_pass(git_diff_foreach(
		diff, test_names_expected, NULL, NULL, NULL, &expect));

	git_diff_free(diff);
	git_tree_free(tree);
	git_index_free(index);
	git_reference_free(head);
	git_reference_free(selfsimilar);
	git_buf_dispose(&one);
	git_buf_dispose(&two);
}