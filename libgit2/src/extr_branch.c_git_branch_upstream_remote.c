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
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_reference__is_branch (char const*) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int not_a_local_branch (char const*) ; 
 int retrieve_upstream_configuration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 

int git_branch_upstream_remote(git_buf *buf, git_repository *repo, const char *refname)
{
	int error;
	git_config *cfg;

	if (!git_reference__is_branch(refname))
		return not_a_local_branch(refname);

	if ((error = git_repository_config__weakptr(&cfg, repo)) < 0)
		return error;

	git_buf_sanitize(buf);

	if ((error = retrieve_upstream_configuration(buf, cfg, refname, "branch.%s.remote")) < 0)
		return error;

	if (git_buf_len(buf) == 0) {
		git_error_set(GIT_ERROR_REFERENCE, "branch '%s' does not have an upstream remote", refname);
		error = GIT_ENOTFOUND;
		git_buf_clear(buf);
	}

	return error;
}