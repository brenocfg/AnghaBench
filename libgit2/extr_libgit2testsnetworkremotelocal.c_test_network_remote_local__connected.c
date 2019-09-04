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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  connect_to_local_repository (int /*<<< orphan*/ ) ; 
 int git_remote_connected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote ; 

void test_network_remote_local__connected(void)
{
	connect_to_local_repository(cl_fixture("testrepo.git"));
	cl_assert(git_remote_connected(remote));

	git_remote_disconnect(remote);
	cl_assert(!git_remote_connected(remote));
}