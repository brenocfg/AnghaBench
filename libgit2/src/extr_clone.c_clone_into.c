#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_6__ {int /*<<< orphan*/  download_tags; scalar_t__ update_fetchhead; } ;
typedef  TYPE_1__ git_fetch_options ;
typedef  int /*<<< orphan*/  git_checkout_options ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_ALL ; 
 int /*<<< orphan*/  assert (int) ; 
 int checkout_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_remote_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

__attribute__((used)) static int clone_into(git_repository *repo, git_remote *_remote, const git_fetch_options *opts, const git_checkout_options *co_opts, const char *branch)
{
	int error;
	git_buf reflog_message = GIT_BUF_INIT;
	git_fetch_options fetch_opts;
	git_remote *remote;

	assert(repo && _remote);

	if (!git_repository_is_empty(repo)) {
		git_error_set(GIT_ERROR_INVALID, "the repository is not empty");
		return -1;
	}

	if ((error = git_remote_dup(&remote, _remote)) < 0)
		return error;

	memcpy(&fetch_opts, opts, sizeof(git_fetch_options));
	fetch_opts.update_fetchhead = 0;
	fetch_opts.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;
	git_buf_printf(&reflog_message, "clone: from %s", git_remote_url(remote));

	if ((error = git_remote_fetch(remote, NULL, &fetch_opts, git_buf_cstr(&reflog_message))) != 0)
		goto cleanup;

	error = checkout_branch(repo, remote, co_opts, branch, git_buf_cstr(&reflog_message));

cleanup:
	git_remote_free(remote);
	git_buf_dispose(&reflog_message);

	return error;
}