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
struct TYPE_4__ {int /*<<< orphan*/  newest_commit; } ;
typedef  TYPE_1__ git_blame_options ;

/* Variables and functions */
 TYPE_1__ GIT_BLAME_OPTIONS_INIT ; 
 int /*<<< orphan*/  check_blame_hunk_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  g_blame ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blame_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_is_shallow (int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_blame_simple__trivial_libgit2(void)
{
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;
	git_object *obj;

	/* If we can't open the libgit2 repo or if it isn't a full repo
	 * with proper history, just skip this test */
	if (git_repository_open(&g_repo, cl_fixture("../..")) < 0)
		cl_skip();

	if (git_repository_is_shallow(g_repo))
		cl_skip();

	if (git_revparse_single(&obj, g_repo, "359fc2d") < 0)
		cl_skip();

	git_oid_cpy(&opts.newest_commit, git_object_id(obj));
	git_object_free(obj);

	cl_git_pass(git_blame_file(&g_blame, g_repo, "include/git2.h", &opts));

	check_blame_hunk_index(g_repo, g_blame,  0,  1, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame,  1,  2, 1, 0, "359fc2d2", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame,  2,  3, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame,  3,  4, 2, 0, "bb742ede", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame,  4,  6, 5, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame,  5, 11, 1, 0, "96fab093", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame,  6, 12, 1, 0, "9d1dcca2", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame,  7, 13, 1, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame,  8, 14, 1, 0, "a15c550d", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame,  9, 15, 1, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 10, 16, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame, 11, 17, 1, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 12, 18, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame, 13, 19, 1, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 14, 20, 1, 0, "638c2ca4", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 15, 21, 1, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 16, 22, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame, 17, 23, 2, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 18, 25, 1, 0, "bf787bd8", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 19, 26, 1, 0, "0984c876", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 20, 27, 1, 0, "2f8a8ab2", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 21, 28, 1, 0, "27df4275", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 22, 29, 1, 0, "a346992f", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 23, 30, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame, 24, 31, 5, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 25, 36, 1, 0, "65b09b1d", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 26, 37, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame, 27, 38, 1, 0, "44908fe7", "src/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 28, 39, 1, 0, "5d4cd003", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 29, 40, 1, 0, "41fb1ca0", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 30, 41, 1, 0, "2dc31040", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 31, 42, 1, 0, "764df57e", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 32, 43, 1, 0, "5280f4e6", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 33, 44, 1, 0, "613d5eb9", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 34, 45, 1, 0, "d12299fe", "src/git.h");
	check_blame_hunk_index(g_repo, g_blame, 35, 46, 1, 0, "111ee3fe", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 36, 47, 1, 0, "f004c4a8", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 37, 48, 1, 0, "111ee3fe", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 38, 49, 1, 0, "9c82357b", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 39, 50, 1, 0, "d6258deb", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 40, 51, 1, 0, "b311e313", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 41, 52, 1, 0, "3412391d", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 42, 53, 1, 0, "bfc9ca59", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 43, 54, 1, 0, "bf477ed4", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 44, 55, 1, 0, "edebceff", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 45, 56, 1, 0, "743a4b3b", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 46, 57, 1, 0, "0a32dca5", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 47, 58, 1, 0, "590fb68b", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 48, 59, 1, 0, "bf477ed4", "include/git2.h");
	check_blame_hunk_index(g_repo, g_blame, 49, 60, 1, 0, "d12299fe", "src/git.h");
}