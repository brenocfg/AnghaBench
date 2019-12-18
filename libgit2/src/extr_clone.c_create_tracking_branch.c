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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int create_branch (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,char const*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int setup_tracking_config (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_tracking_branch(
	git_reference **branch,
	git_repository *repo,
	const git_oid *target,
	const char *branch_name,
	const char *log_message)
{
	int error;

	if ((error = create_branch(branch, repo, target, branch_name, log_message)) < 0)
		return error;

	return setup_tracking_config(
		repo,
		branch_name,
		GIT_REMOTE_ORIGIN,
		git_reference_name(*branch));
}