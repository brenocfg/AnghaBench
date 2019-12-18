#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fetch_refspecs ; 
 int /*<<< orphan*/  git_remote_add_fetch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_add_push (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create_with_fetchspec (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_delete (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_get_fetch_refspecs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_get_push_refspecs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * push_refspecs ; 

void test_network_remote_remotes__query_refspecs(void)
{
	git_remote *remote;
	git_strarray array;
	int i;

	cl_git_pass(git_remote_create_with_fetchspec(&remote, _repo, "query", "git://github.com/libgit2/libgit2", NULL));
	git_remote_free(remote);

	for (i = 0; i < 3; i++) {
		cl_git_pass(git_remote_add_fetch(_repo, "query", fetch_refspecs[i]));
		cl_git_pass(git_remote_add_push(_repo, "query", push_refspecs[i]));
	}

	cl_git_pass(git_remote_lookup(&remote, _repo, "query"));

	cl_git_pass(git_remote_get_fetch_refspecs(&array, remote));
	for (i = 0; i < 3; i++) {
		cl_assert_equal_s(fetch_refspecs[i], array.strings[i]);
	}
	git_strarray_free(&array);

	cl_git_pass(git_remote_get_push_refspecs(&array, remote));
	for (i = 0; i < 3; i++) {
		cl_assert_equal_s(push_refspecs[i], array.strings[i]);
	}
	git_strarray_free(&array);

	git_remote_free(remote);
	git_remote_delete(_repo, "test");
}