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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_switch_branches(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	git_object *obj = NULL;

	assert_on_branch(g_repo, "master");

	/* do first checkout with FORCE because we don't know if testrepo
	 * base data is clean for a checkout or not
	 */
	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/dir"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/dir"));

	cl_assert(git_path_isfile("testrepo/README"));
	cl_assert(git_path_isfile("testrepo/branch_file.txt"));
	cl_assert(git_path_isfile("testrepo/new.txt"));
	cl_assert(git_path_isfile("testrepo/a/b.txt"));

	cl_assert(!git_path_isdir("testrepo/ab"));

	assert_on_branch(g_repo, "dir");

	git_object_free(obj);

	/* do second checkout safe because we should be clean after first */
	opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/subtrees"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/subtrees"));

	cl_assert(git_path_isfile("testrepo/README"));
	cl_assert(git_path_isfile("testrepo/branch_file.txt"));
	cl_assert(git_path_isfile("testrepo/new.txt"));
	cl_assert(git_path_isfile("testrepo/ab/4.txt"));
	cl_assert(git_path_isfile("testrepo/ab/c/3.txt"));
	cl_assert(git_path_isfile("testrepo/ab/de/2.txt"));
	cl_assert(git_path_isfile("testrepo/ab/de/fgh/1.txt"));

	cl_assert(!git_path_isdir("testrepo/a"));

	assert_on_branch(g_repo, "subtrees");

	git_object_free(obj);
}