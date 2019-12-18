#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_MASTER_FILE ; 
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_refspec_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_remote__matching_refspec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_remote_default_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_remote_ls (TYPE_1__ const***,size_t*,int /*<<< orphan*/ *) ; 
 int git_repository_set_head_detached (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int setup_tracking_config (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int update_head_to_new_branch (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int update_head_to_remote(
		git_repository *repo,
		git_remote *remote,
		const char *reflog_message)
{
	int error = 0;
	size_t refs_len;
	git_refspec *refspec;
	const git_remote_head *remote_head, **refs;
	const git_oid *remote_head_id;
	git_buf remote_master_name = GIT_BUF_INIT;
	git_buf branch = GIT_BUF_INIT;

	if ((error = git_remote_ls(&refs, &refs_len, remote)) < 0)
		return error;

	/* We cloned an empty repository or one with an unborn HEAD */
	if (refs_len == 0 || strcmp(refs[0]->name, GIT_HEAD_FILE))
		return setup_tracking_config(
			repo, "master", GIT_REMOTE_ORIGIN, GIT_REFS_HEADS_MASTER_FILE);

	/* We know we have HEAD, let's see where it points */
	remote_head = refs[0];
	assert(remote_head);

	remote_head_id = &remote_head->oid;

	error = git_remote_default_branch(&branch, remote);
	if (error == GIT_ENOTFOUND) {
		error = git_repository_set_head_detached(
			repo, remote_head_id);
		goto cleanup;
	}

	refspec = git_remote__matching_refspec(remote, git_buf_cstr(&branch));

	if (refspec == NULL) {
		git_error_set(GIT_ERROR_NET, "the remote's default branch does not fit the refspec configuration");
		error = GIT_EINVALIDSPEC;
		goto cleanup;
	}

	/* Determine the remote tracking reference name from the local master */
	if ((error = git_refspec_transform(
		&remote_master_name,
		refspec,
		git_buf_cstr(&branch))) < 0)
		goto cleanup;

	error = update_head_to_new_branch(
		repo,
		remote_head_id,
		git_buf_cstr(&branch),
		reflog_message);

cleanup:
	git_buf_dispose(&remote_master_name);
	git_buf_dispose(&branch);

	return error;
}