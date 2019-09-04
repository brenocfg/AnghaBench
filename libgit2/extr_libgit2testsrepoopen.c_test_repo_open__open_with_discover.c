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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

void test_repo_open__open_with_discover(void)
{
	static const char *variants[] = {
		"attr", "attr/", "attr/.git", "attr/.git/",
		"attr/sub", "attr/sub/", "attr/sub/sub", "attr/sub/sub/",
		NULL
	};
	git_repository *repo;
	const char **scan;

	cl_fixture_sandbox("attr");
	cl_git_pass(p_rename("attr/.gitted", "attr/.git"));

	for (scan = variants; *scan != NULL; scan++) {
		cl_git_pass(git_repository_open_ext(&repo, *scan, 0, NULL));
		cl_assert(git__suffixcmp(git_repository_path(repo), "attr/.git/") == 0);
		cl_assert(git__suffixcmp(git_repository_workdir(repo), "attr/") == 0);
		git_repository_free(repo);
	}

	cl_fixture_cleanup("attr");
}