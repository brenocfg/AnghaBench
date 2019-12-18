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
 int /*<<< orphan*/  cl_assert_equal_i (size_t,int) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_to_local_repository (char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_ls (int /*<<< orphan*/  const***,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 
 int /*<<< orphan*/ * remote ; 

void test_network_remote_local__retrieve_advertised_references_from_spaced_repository(void)
{
	const git_remote_head **refs;
	size_t refs_len;

	cl_fixture_sandbox("testrepo.git");
	cl_git_pass(p_rename("testrepo.git", "spaced testrepo.git"));

	connect_to_local_repository("spaced testrepo.git");

	cl_git_pass(git_remote_ls(&refs, &refs_len, remote));

	cl_assert_equal_i(refs_len, 29);

	git_remote_free(remote);	/* Disconnect from the "spaced repo" before the cleanup */
	remote = NULL;

	cl_fixture_cleanup("spaced testrepo.git");
}