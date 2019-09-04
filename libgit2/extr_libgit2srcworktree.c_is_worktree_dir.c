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
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_path_contains_file (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool is_worktree_dir(const char *dir)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if (git_buf_sets(&buf, dir) < 0)
		return -1;

	error = git_path_contains_file(&buf, "commondir")
		&& git_path_contains_file(&buf, "gitdir")
		&& git_path_contains_file(&buf, "HEAD");

	git_buf_dispose(&buf);
	return error;
}