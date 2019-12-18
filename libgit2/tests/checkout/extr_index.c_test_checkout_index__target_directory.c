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
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  checkout_count_callback ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void test_checkout_index__target_directory(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	checkout_counts cts;
	memset(&cts, 0, sizeof(cts));

	opts.checkout_strategy = GIT_CHECKOUT_SAFE |
		GIT_CHECKOUT_RECREATE_MISSING;
	opts.target_directory = "alternative";
	cl_assert(!git_path_isdir("alternative"));

	opts.notify_flags = GIT_CHECKOUT_NOTIFY_ALL;
	opts.notify_cb = checkout_count_callback;
	opts.notify_payload = &cts;

	/* create some files that *would* conflict if we were using the wd */
	cl_git_mkfile("testrepo/README", "I'm in the way!\n");
	cl_git_mkfile("testrepo/new.txt", "my new file\n");

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	cl_assert_equal_i(0, cts.n_untracked);
	cl_assert_equal_i(0, cts.n_ignored);
	cl_assert_equal_i(4, cts.n_updates);

	check_file_contents("./alternative/README", "hey there\n");
	check_file_contents("./alternative/branch_file.txt", "hi\nbye!\n");
	check_file_contents("./alternative/new.txt", "my new file\n");

	cl_git_pass(git_futils_rmdir_r(
		"alternative", NULL, GIT_RMDIR_REMOVE_FILES));
}