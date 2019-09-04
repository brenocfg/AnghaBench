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
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 int /*<<< orphan*/  GIT_BRANCH_REMOTE ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 scalar_t__ git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int git_branch_remote_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_config_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_reference__is_branch (char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 char* git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference_owner (int /*<<< orphan*/ *) ; 
 scalar_t__ git_refspec_rtransform (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * git_remote__matching_dst_refspec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int not_a_local_branch (char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int unset_upstream (int /*<<< orphan*/ *,char const*) ; 

int git_branch_set_upstream(git_reference *branch, const char *upstream_name)
{
	git_buf key = GIT_BUF_INIT, value = GIT_BUF_INIT;
	git_reference *upstream;
	git_repository *repo;
	git_remote *remote = NULL;
	git_config *config;
	const char *name, *shortname;
	int local, error;
	const git_refspec *fetchspec;

	name = git_reference_name(branch);
	if (!git_reference__is_branch(name))
		return not_a_local_branch(name);

	if (git_repository_config__weakptr(&config, git_reference_owner(branch)) < 0)
		return -1;

	shortname = name + strlen(GIT_REFS_HEADS_DIR);

	if (upstream_name == NULL)
		return unset_upstream(config, shortname);

	repo = git_reference_owner(branch);

	/* First we need to figure out whether it's a branch or remote-tracking */
	if (git_branch_lookup(&upstream, repo, upstream_name, GIT_BRANCH_LOCAL) == 0)
		local = 1;
	else if (git_branch_lookup(&upstream, repo, upstream_name, GIT_BRANCH_REMOTE) == 0)
		local = 0;
	else {
		git_error_set(GIT_ERROR_REFERENCE,
			"cannot set upstream for branch '%s'", shortname);
		return GIT_ENOTFOUND;
	}

	/*
	 * If it's local, the remote is "." and the branch name is
	 * simply the refname. Otherwise we need to figure out what
	 * the remote-tracking branch's name on the remote is and use
	 * that.
	 */
	if (local)
		error = git_buf_puts(&value, ".");
	else
		error = git_branch_remote_name(&value, repo, git_reference_name(upstream));

	if (error < 0)
		goto on_error;

	if (git_buf_printf(&key, "branch.%s.remote", shortname) < 0)
		goto on_error;

	if (git_config_set_string(config, git_buf_cstr(&key), git_buf_cstr(&value)) < 0)
		goto on_error;

	if (local) {
		git_buf_clear(&value);
		if (git_buf_puts(&value, git_reference_name(upstream)) < 0)
			goto on_error;
	} else {
		/* Get the remoe-tracking branch's refname in its repo */
		if (git_remote_lookup(&remote, repo, git_buf_cstr(&value)) < 0)
			goto on_error;

		fetchspec = git_remote__matching_dst_refspec(remote, git_reference_name(upstream));
		git_buf_clear(&value);
		if (!fetchspec || git_refspec_rtransform(&value, fetchspec, git_reference_name(upstream)) < 0)
			goto on_error;

		git_remote_free(remote);
		remote = NULL;
	}

	git_buf_clear(&key);
	if (git_buf_printf(&key, "branch.%s.merge", shortname) < 0)
		goto on_error;

	if (git_config_set_string(config, git_buf_cstr(&key), git_buf_cstr(&value)) < 0)
		goto on_error;

	git_reference_free(upstream);
	git_buf_dispose(&key);
	git_buf_dispose(&value);

	return 0;

on_error:
	git_reference_free(upstream);
	git_buf_dispose(&key);
	git_buf_dispose(&value);
	git_remote_free(remote);

	return -1;
}