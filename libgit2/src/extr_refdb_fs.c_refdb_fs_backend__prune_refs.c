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
struct TYPE_3__ {int /*<<< orphan*/  commonpath; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_RMDIR_EMPTY_PARENTS ; 
 int GIT_RMDIR_SKIP_ROOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_join3 (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char const*,int /*<<< orphan*/ ,int) ; 
 size_t git_path_common_dirlen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_squash_slashes (int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void refdb_fs_backend__prune_refs(
	refdb_fs_backend *backend,
	const char *ref_name,
	const char *prefix)
{
	git_buf relative_path = GIT_BUF_INIT;
	git_buf base_path = GIT_BUF_INIT;
	size_t commonlen;

	assert(backend && ref_name);

	if (git_buf_sets(&relative_path, ref_name) < 0)
		goto cleanup;

	git_path_squash_slashes(&relative_path);
	if ((commonlen = git_path_common_dirlen("refs/heads/", git_buf_cstr(&relative_path))) == strlen("refs/heads/") ||
		(commonlen = git_path_common_dirlen("refs/tags/", git_buf_cstr(&relative_path))) == strlen("refs/tags/") ||
		(commonlen = git_path_common_dirlen("refs/remotes/", git_buf_cstr(&relative_path))) == strlen("refs/remotes/")) {

		git_buf_truncate(&relative_path, commonlen);

		if (prefix) {
			if (git_buf_join3(&base_path, '/', backend->commonpath, prefix, git_buf_cstr(&relative_path)) < 0)
				goto cleanup;
		} else {
			if (git_buf_joinpath(&base_path, backend->commonpath, git_buf_cstr(&relative_path)) < 0)
				goto cleanup;
		}

		git_futils_rmdir_r(ref_name + commonlen, git_buf_cstr(&base_path), GIT_RMDIR_EMPTY_PARENTS | GIT_RMDIR_SKIP_ROOT);
	}

cleanup:
	git_buf_dispose(&relative_path);
	git_buf_dispose(&base_path);
}