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

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_path_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_path_buf ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create_anonymous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_ls (int /*<<< orphan*/  const***,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote ; 
 int /*<<< orphan*/  repo ; 

void test_network_remote_local__retrieve_advertised_before_connect(void)
{
	const git_remote_head **refs;
	size_t refs_len = 0;

	git_buf_sets(&file_path_buf, cl_git_path_url(cl_fixture("testrepo.git")));

	cl_git_pass(git_remote_create_anonymous(&remote, repo, git_buf_cstr(&file_path_buf)));
	cl_git_fail(git_remote_ls(&refs, &refs_len, remote));
}