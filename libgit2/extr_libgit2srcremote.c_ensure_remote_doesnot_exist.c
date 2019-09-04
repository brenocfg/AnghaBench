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
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int ensure_remote_doesnot_exist(git_repository *repo, const char *name)
{
	int error;
	git_remote *remote;

	error = git_remote_lookup(&remote, repo, name);

	if (error == GIT_ENOTFOUND)
		return 0;

	if (error < 0)
		return error;

	git_remote_free(remote);

	git_error_set(GIT_ERROR_CONFIG, "remote '%s' already exists", name);

	return GIT_EEXISTS;
}