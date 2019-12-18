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
struct TYPE_3__ {int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_filebuf ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_PATH_REJECT_FILESYSTEM_DEFAULTS ; 
 int /*<<< orphan*/  GIT_REFLOG_FILE_MODE ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ retrieve_reflog_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int lock_reflog(git_filebuf *file, refdb_fs_backend *backend, const char *refname)
{
	git_repository *repo;
	git_buf log_path = GIT_BUF_INIT;
	int error;

	repo = backend->repo;

	if (!git_path_isvalid(backend->repo, refname, 0, GIT_PATH_REJECT_FILESYSTEM_DEFAULTS)) {
		git_error_set(GIT_ERROR_INVALID, "invalid reference name '%s'", refname);
		return GIT_EINVALIDSPEC;
	}

	if (retrieve_reflog_path(&log_path, repo, refname) < 0)
		return -1;

	if (!git_path_isfile(git_buf_cstr(&log_path))) {
		git_error_set(GIT_ERROR_INVALID,
			"log file for reference '%s' doesn't exist", refname);
		error = -1;
		goto cleanup;
	}

	error = git_filebuf_open(file, git_buf_cstr(&log_path), 0, GIT_REFLOG_FILE_MODE);

cleanup:
	git_buf_dispose(&log_path);

	return error;
}