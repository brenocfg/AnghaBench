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
typedef  int /*<<< orphan*/  git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_ls (int /*<<< orphan*/  const***,size_t*,int /*<<< orphan*/ *) ; 

void test_online_fetch__ls_disconnected(void)
{
	const git_remote_head **refs;
	size_t refs_len_before, refs_len_after;
	git_remote *remote;

	cl_git_pass(git_remote_create(&remote, _repo, "test",
				"http://github.com/libgit2/TestGitRepository.git"));
	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));
	cl_git_pass(git_remote_ls(&refs, &refs_len_before, remote));
	git_remote_disconnect(remote);
	cl_git_pass(git_remote_ls(&refs, &refs_len_after, remote));

	cl_assert_equal_i(refs_len_before, refs_len_after);

	git_remote_free(remote);
}