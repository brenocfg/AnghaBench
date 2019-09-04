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
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int repo_init_create_origin(git_repository *repo, const char *url)
{
	int error;
	git_remote *remote;

	if (!(error = git_remote_create(&remote, repo, GIT_REMOTE_ORIGIN, url))) {
		git_remote_free(remote);
	}

	return error;
}