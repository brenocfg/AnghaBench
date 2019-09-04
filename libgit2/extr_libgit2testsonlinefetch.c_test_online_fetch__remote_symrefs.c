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
struct TYPE_3__ {int /*<<< orphan*/  symref_target; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_ls (TYPE_1__ const***,size_t*,int /*<<< orphan*/ *) ; 

void test_online_fetch__remote_symrefs(void)
{
	const git_remote_head **refs;
	size_t refs_len;
	git_remote *remote;

	cl_git_pass(git_remote_create(&remote, _repo, "test",
				"http://github.com/libgit2/TestGitRepository.git"));
	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));
	git_remote_disconnect(remote);
	cl_git_pass(git_remote_ls(&refs, &refs_len, remote));

	cl_assert_equal_s("HEAD", refs[0]->name);
	cl_assert_equal_s("refs/heads/master", refs[0]->symref_target);

	git_remote_free(remote);
}