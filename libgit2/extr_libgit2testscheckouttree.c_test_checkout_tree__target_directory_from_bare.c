#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {int checkout_strategy; char* target_directory; TYPE_2__* notify_payload; int /*<<< orphan*/  notify_cb; int /*<<< orphan*/  notify_flags; } ;
typedef  TYPE_1__ git_checkout_options ;
typedef  int /*<<< orphan*/  cts ;
struct TYPE_7__ {int /*<<< orphan*/  n_updates; int /*<<< orphan*/  n_ignored; int /*<<< orphan*/  n_untracked; } ;
typedef  TYPE_2__ checkout_counts ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_ALL ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  check_file_contents_nocr (char*,char*) ; 
 int /*<<< orphan*/  checkout_count_callback ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_object ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_checkout_tree__cleanup () ; 

void test_checkout_tree__target_directory_from_bare(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	checkout_counts cts;
	memset(&cts, 0, sizeof(cts));

	test_checkout_tree__cleanup(); /* cleanup default checkout */

	g_repo = cl_git_sandbox_init("testrepo.git");
	cl_assert(git_repository_is_bare(g_repo));

	opts.checkout_strategy = GIT_CHECKOUT_SAFE |
		GIT_CHECKOUT_RECREATE_MISSING;

	opts.notify_flags = GIT_CHECKOUT_NOTIFY_ALL;
	opts.notify_cb = checkout_count_callback;
	opts.notify_payload = &cts;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "HEAD"));
	cl_git_pass(git_object_lookup(&g_object, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_fail(git_checkout_tree(g_repo, g_object, &opts));

	opts.target_directory = "alternative";
	cl_assert(!git_path_isdir("alternative"));

	cl_git_pass(git_checkout_tree(g_repo, g_object, &opts));

	cl_assert_equal_i(0, cts.n_untracked);
	cl_assert_equal_i(0, cts.n_ignored);
	cl_assert_equal_i(3, cts.n_updates);

	check_file_contents_nocr("./alternative/README", "hey there\n");
	check_file_contents_nocr("./alternative/branch_file.txt", "hi\nbye!\n");
	check_file_contents_nocr("./alternative/new.txt", "my new file\n");

	cl_git_pass(git_futils_rmdir_r(
		"alternative", NULL, GIT_RMDIR_REMOVE_FILES));
}