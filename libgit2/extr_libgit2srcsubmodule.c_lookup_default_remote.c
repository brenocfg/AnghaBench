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

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int lookup_head_remote (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lookup_default_remote(git_remote **remote, git_repository *repo)
{
	int error = lookup_head_remote(remote, repo);

	/* if that failed, use 'origin' instead */
	if (error == GIT_ENOTFOUND)
		error = git_remote_lookup(remote, repo, "origin");

	if (error == GIT_ENOTFOUND)
		git_error_set(
			GIT_ERROR_SUBMODULE,
			"cannot get default remote for submodule - no local tracking "
			"branch for HEAD and origin does not exist");

	return error;
}