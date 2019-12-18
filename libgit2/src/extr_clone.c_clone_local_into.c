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
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_fetch_options ;
typedef  int /*<<< orphan*/  git_checkout_options ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_CPDIR_LINK_FILES ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_OBJECT_DIR_MODE ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_OBJECTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ can_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int checkout_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_cp_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int git_path_from_url_or_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_item_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clone_local_into(git_repository *repo, git_remote *remote, const git_fetch_options *fetch_opts, const git_checkout_options *co_opts, const char *branch, int link)
{
	int error, flags;
	git_repository *src;
	git_buf src_odb = GIT_BUF_INIT, dst_odb = GIT_BUF_INIT, src_path = GIT_BUF_INIT;
	git_buf reflog_message = GIT_BUF_INIT;

	assert(repo && remote);

	if (!git_repository_is_empty(repo)) {
		git_error_set(GIT_ERROR_INVALID, "the repository is not empty");
		return -1;
	}

	/*
	 * Let's figure out what path we should use for the source
	 * repo, if it's not rooted, the path should be relative to
	 * the repository's worktree/gitdir.
	 */
	if ((error = git_path_from_url_or_path(&src_path, git_remote_url(remote))) < 0)
		return error;

	/* Copy .git/objects/ from the source to the target */
	if ((error = git_repository_open(&src, git_buf_cstr(&src_path))) < 0) {
		git_buf_dispose(&src_path);
		return error;
	}

	if (git_repository_item_path(&src_odb, src, GIT_REPOSITORY_ITEM_OBJECTS) < 0
		|| git_repository_item_path(&dst_odb, repo, GIT_REPOSITORY_ITEM_OBJECTS) < 0) {
		error = -1;
		goto cleanup;
	}

	flags = 0;
	if (can_link(git_repository_path(src), git_repository_path(repo), link))
		flags |= GIT_CPDIR_LINK_FILES;

	error = git_futils_cp_r(git_buf_cstr(&src_odb), git_buf_cstr(&dst_odb),
				flags, GIT_OBJECT_DIR_MODE);

	/*
	 * can_link() doesn't catch all variations, so if we hit an
	 * error and did want to link, let's try again without trying
	 * to link.
	 */
	if (error < 0 && link) {
		flags &= ~GIT_CPDIR_LINK_FILES;
		error = git_futils_cp_r(git_buf_cstr(&src_odb), git_buf_cstr(&dst_odb),
					flags, GIT_OBJECT_DIR_MODE);
	}

	if (error < 0)
		goto cleanup;

	git_buf_printf(&reflog_message, "clone: from %s", git_remote_url(remote));

	if ((error = git_remote_fetch(remote, NULL, fetch_opts, git_buf_cstr(&reflog_message))) != 0)
		goto cleanup;

	error = checkout_branch(repo, remote, co_opts, branch, git_buf_cstr(&reflog_message));

cleanup:
	git_buf_dispose(&reflog_message);
	git_buf_dispose(&src_path);
	git_buf_dispose(&src_odb);
	git_buf_dispose(&dst_odb);
	git_repository_free(src);
	return error;
}