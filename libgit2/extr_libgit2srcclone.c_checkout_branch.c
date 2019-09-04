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
typedef  int /*<<< orphan*/  git_checkout_options ;

/* Variables and functions */
 int git_checkout_head (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ *) ; 
 scalar_t__ should_checkout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int update_head_to_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int update_head_to_remote (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int checkout_branch(git_repository *repo, git_remote *remote, const git_checkout_options *co_opts, const char *branch, const char *reflog_message)
{
	int error;

	if (branch)
		error = update_head_to_branch(repo, git_remote_name(remote), branch,
				reflog_message);
	/* Point HEAD to the same ref as the remote's head */
	else
		error = update_head_to_remote(repo, remote, reflog_message);

	if (!error && should_checkout(repo, git_repository_is_bare(repo), co_opts))
		error = git_checkout_head(repo, co_opts);

	return error;
}