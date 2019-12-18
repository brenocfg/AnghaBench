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
typedef  int DWORD ;

/* Variables and functions */
 int FILE_ATTRIBUTE_HIDDEN ; 
 int GetFileAttributes (char const*) ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__suffixcmp (char const*,char const*) ; 
 int /*<<< orphan*/  git_path_isdir (char const*) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char const*,int) ; 
 int git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int git_repository_is_empty (int /*<<< orphan*/ ) ; 
 char const* git_repository_path (int /*<<< orphan*/ ) ; 
 char* git_repository_workdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ensure_repository_init(
	const char *working_directory,
	int is_bare,
	const char *expected_path_repository,
	const char *expected_working_directory)
{
	const char *workdir;

	cl_assert(!git_path_isdir(working_directory));

	cl_git_pass(git_repository_init(&_repo, working_directory, is_bare));

	workdir = git_repository_workdir(_repo);
	if (workdir != NULL || expected_working_directory != NULL) {
		cl_assert(
			git__suffixcmp(workdir, expected_working_directory) == 0
		);
	}

	cl_assert(
		git__suffixcmp(git_repository_path(_repo), expected_path_repository) == 0
	);

	cl_assert(git_repository_is_bare(_repo) == is_bare);

#ifdef GIT_WIN32
	if (!is_bare) {
		DWORD fattrs = GetFileAttributes(git_repository_path(_repo));
		cl_assert((fattrs & FILE_ATTRIBUTE_HIDDEN) != 0);
	}
#endif

	cl_assert(git_repository_is_empty(_repo));
}