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
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_remote_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_network_remote_remotes__list(void)
{
	git_strarray list;
	git_config *cfg;

	cl_git_pass(git_remote_list(&list, _repo));
	cl_assert(list.count == 5);
	git_strarray_free(&list);

	cl_git_pass(git_repository_config(&cfg, _repo));

	/* Create a new remote */
	cl_git_pass(git_config_set_string(cfg, "remote.specless.url", "http://example.com"));

	/* Update a remote (previously without any url/pushurl entry) */
	cl_git_pass(git_config_set_string(cfg, "remote.no-remote-url.pushurl", "http://example.com"));

	cl_git_pass(git_remote_list(&list, _repo));
	cl_assert(list.count == 7);
	git_strarray_free(&list);

	git_config_free(cfg);
}