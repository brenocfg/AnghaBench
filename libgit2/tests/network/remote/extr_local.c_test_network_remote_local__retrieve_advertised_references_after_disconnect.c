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
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_to_local_repository (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_ls (int /*<<< orphan*/  const***,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote ; 

void test_network_remote_local__retrieve_advertised_references_after_disconnect(void)
{
	const git_remote_head **refs;
	size_t refs_len;

	connect_to_local_repository(cl_fixture("testrepo.git"));
	git_remote_disconnect(remote);

	cl_git_pass(git_remote_ls(&refs, &refs_len, remote));

	cl_assert_equal_i(refs_len, 29);
}