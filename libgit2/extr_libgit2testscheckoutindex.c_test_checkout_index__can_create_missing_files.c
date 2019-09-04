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
struct TYPE_4__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 

void test_checkout_index__can_create_missing_files(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	cl_assert_equal_i(false, git_path_isfile("./testrepo/README"));
	cl_assert_equal_i(false, git_path_isfile("./testrepo/branch_file.txt"));
	cl_assert_equal_i(false, git_path_isfile("./testrepo/new.txt"));

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	check_file_contents("./testrepo/README", "hey there\n");
	check_file_contents("./testrepo/branch_file.txt", "hi\nbye!\n");
	check_file_contents("./testrepo/new.txt", "my new file\n");
}