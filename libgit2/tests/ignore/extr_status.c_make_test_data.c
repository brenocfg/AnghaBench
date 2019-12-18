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

/* Variables and functions */
 int GIT_MKDIR_PATH ; 
 int GIT_MKDIR_SKIP_LAST ; 
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char const*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_futils_mkdir_relative (char const*,char const*,int,int,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void make_test_data(const char *reponame, const char **files)
{
	const char **scan;
	size_t repolen = strlen(reponame) + 1;

	g_repo = cl_git_sandbox_init(reponame);

	for (scan = files; *scan != NULL; ++scan) {
		cl_git_pass(git_futils_mkdir_relative(
			*scan + repolen, reponame,
			0777, GIT_MKDIR_PATH | GIT_MKDIR_SKIP_LAST, NULL));
		cl_git_mkfile(*scan, "contents");
	}
}