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
 char* GIT_REFS_REMOTES_DIR ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 char* git_repository_path (int /*<<< orphan*/ ) ; 
 int p_mkdir (char*,int) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static int create_remote_tracking_branch(const char *branch_name, const char *oid_str)
{
	int error = 0;

	git_buf remotes_path = GIT_BUF_INIT,
		origin_path = GIT_BUF_INIT,
		filename = GIT_BUF_INIT,
		data = GIT_BUF_INIT;

	if ((error = git_buf_puts(&remotes_path, git_repository_path(repo))) < 0 ||
		(error = git_buf_puts(&remotes_path, GIT_REFS_REMOTES_DIR)) < 0)
		goto done;

	if (!git_path_exists(git_buf_cstr(&remotes_path)) &&
		(error = p_mkdir(git_buf_cstr(&remotes_path), 0777)) < 0)
		goto done;

	if ((error = git_buf_puts(&origin_path, git_buf_cstr(&remotes_path))) < 0 ||
		(error = git_buf_puts(&origin_path, "origin")) < 0)
		goto done;

	if (!git_path_exists(git_buf_cstr(&origin_path)) &&
		(error = p_mkdir(git_buf_cstr(&origin_path), 0777)) < 0)
		goto done;

	if ((error = git_buf_puts(&filename, git_buf_cstr(&origin_path))) < 0 ||
		(error = git_buf_puts(&filename, "/")) < 0 ||
		(error = git_buf_puts(&filename, branch_name)) < 0 ||
		(error = git_buf_puts(&data, oid_str)) < 0 ||
		(error = git_buf_puts(&data, "\n")) < 0)
		goto done;

	cl_git_rewritefile(git_buf_cstr(&filename), git_buf_cstr(&data));

done:
	git_buf_dispose(&remotes_path);
	git_buf_dispose(&origin_path);
	git_buf_dispose(&filename);
	git_buf_dispose(&data);

	return error;
}