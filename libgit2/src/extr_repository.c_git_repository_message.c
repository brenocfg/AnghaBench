#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gitdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_MERGE_MSG_FILE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_readbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int p_stat (int /*<<< orphan*/ ,struct stat*) ; 

int git_repository_message(git_buf *out, git_repository *repo)
{
	git_buf path = GIT_BUF_INIT;
	struct stat st;
	int error;

	git_buf_sanitize(out);

	if (git_buf_joinpath(&path, repo->gitdir, GIT_MERGE_MSG_FILE) < 0)
		return -1;

	if ((error = p_stat(git_buf_cstr(&path), &st)) < 0) {
		if (errno == ENOENT)
			error = GIT_ENOTFOUND;
		git_error_set(GIT_ERROR_OS, "could not access message file");
	} else {
		error = git_futils_readbuffer(out, git_buf_cstr(&path));
	}

	git_buf_dispose(&path);

	return error;
}