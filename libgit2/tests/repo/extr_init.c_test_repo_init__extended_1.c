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
struct stat {int st_mode; } ;
struct TYPE_4__ {int flags; char* workdir_path; char* description; char* initial_head; char* origin_url; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_repository_init_options ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 int GIT_REPOSITORY_INIT_NO_DOTGIT_DIR ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_SHARED_GROUP ; 
 int S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_is_chmod_supported () ; 
 int /*<<< orphan*/  git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_path_lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 

void test_repo_init__extended_1(void)
{
	git_reference *ref;
	git_remote *remote;
	struct stat st;
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;

	opts.flags = GIT_REPOSITORY_INIT_MKPATH |
		GIT_REPOSITORY_INIT_NO_DOTGIT_DIR;
	opts.mode = GIT_REPOSITORY_INIT_SHARED_GROUP;
	opts.workdir_path = "../c_wd";
	opts.description = "Awesomest test repository evah";
	opts.initial_head = "development";
	opts.origin_url = "https://github.com/libgit2/libgit2.git";

	cl_git_pass(git_repository_init_ext(&_repo, "root/b/c.git", &opts));

	cl_assert(!git__suffixcmp(git_repository_workdir(_repo), "/c_wd/"));
	cl_assert(!git__suffixcmp(git_repository_path(_repo), "/c.git/"));
	cl_assert(git_path_isfile("root/b/c_wd/.git"));
	cl_assert(!git_repository_is_bare(_repo));
	/* repo will not be counted as empty because we set head to "development" */
	cl_assert(!git_repository_is_empty(_repo));

	cl_git_pass(git_path_lstat(git_repository_path(_repo), &st));
	cl_assert(S_ISDIR(st.st_mode));
	if (cl_is_chmod_supported())
		cl_assert((S_ISGID & st.st_mode) == S_ISGID);
	else
		cl_assert((S_ISGID & st.st_mode) == 0);

	cl_git_pass(git_reference_lookup(&ref, _repo, "HEAD"));
	cl_assert(git_reference_type(ref) == GIT_REFERENCE_SYMBOLIC);
	cl_assert_equal_s("refs/heads/development", git_reference_symbolic_target(ref));
	git_reference_free(ref);

	cl_git_pass(git_remote_lookup(&remote, _repo, "origin"));
	cl_assert_equal_s("origin", git_remote_name(remote));
	cl_assert_equal_s(opts.origin_url, git_remote_url(remote));
	git_remote_free(remote);

	git_repository_free(_repo);
	cl_fixture_cleanup("root");
}