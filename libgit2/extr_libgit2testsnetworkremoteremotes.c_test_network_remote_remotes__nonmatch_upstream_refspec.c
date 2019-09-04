#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** member_0; int member_1; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_network_remote_remotes__nonmatch_upstream_refspec(void)
{
	git_config *config;
	git_remote *remote;
	char *specstr[] = {
		"refs/tags/*:refs/tags/*",
	};
	git_strarray specs = {
		specstr,
		1,
	};

	cl_git_pass(git_remote_create(&remote, _repo, "taggy", git_repository_path(_repo)));

	/*
	 * Set the current branch's upstream remote to a dummy ref so we call into the code
	 * which tries to check for the current branch's upstream in the refspecs
	 */
	cl_git_pass(git_repository_config(&config, _repo));
	cl_git_pass(git_config_set_string(config, "branch.master.remote", "taggy"));
	cl_git_pass(git_config_set_string(config, "branch.master.merge", "refs/heads/foo"));

	cl_git_pass(git_remote_fetch(remote, &specs, NULL, NULL));

	git_remote_free(remote);
}