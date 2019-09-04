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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,char const*,char*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_filesystem_case_insensitive(const char *gitdir_path)
{
	git_buf path = GIT_BUF_INIT;
	int is_insensitive = -1;

	if (!git_buf_joinpath(&path, gitdir_path, "CoNfIg"))
		is_insensitive = git_path_exists(git_buf_cstr(&path));

	git_buf_dispose(&path);
	return is_insensitive;
}