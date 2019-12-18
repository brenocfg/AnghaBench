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
 int GIT_CHECKOUT_REMOVE_UNTRACKED ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  check_file_contents_nocr (char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_checkout_index__can_update_prefixed_files(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	cl_assert_equal_i(false, git_path_isfile("./testrepo/README"));
	cl_assert_equal_i(false, git_path_isfile("./testrepo/branch_file.txt"));
	cl_assert_equal_i(false, git_path_isfile("./testrepo/new.txt"));

	cl_git_mkfile("./testrepo/READ", "content\n");
	cl_git_mkfile("./testrepo/README.after", "content\n");
	cl_git_pass(p_mkdir("./testrepo/branch_file", 0777));
	cl_git_pass(p_mkdir("./testrepo/branch_file/contained_dir", 0777));
	cl_git_mkfile("./testrepo/branch_file/contained_file", "content\n");
	cl_git_pass(p_mkdir("./testrepo/branch_file.txt.after", 0777));

	opts.checkout_strategy =
		GIT_CHECKOUT_SAFE |
		GIT_CHECKOUT_RECREATE_MISSING |
		GIT_CHECKOUT_REMOVE_UNTRACKED;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	/* remove untracked will remove the .gitattributes file before the blobs
	 * were created, so they will have had crlf filtering applied on Windows
	 */
	check_file_contents_nocr("./testrepo/README", "hey there\n");
	check_file_contents_nocr("./testrepo/branch_file.txt", "hi\nbye!\n");
	check_file_contents_nocr("./testrepo/new.txt", "my new file\n");

	cl_assert(!git_path_exists("testrepo/READ"));
	cl_assert(!git_path_exists("testrepo/README.after"));
	cl_assert(!git_path_exists("testrepo/branch_file"));
	cl_assert(!git_path_exists("testrepo/branch_file.txt.after"));
}