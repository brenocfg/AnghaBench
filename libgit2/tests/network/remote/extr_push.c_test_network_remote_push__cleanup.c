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
 int /*<<< orphan*/ * _dummy ; 
 int /*<<< orphan*/ * _remote ; 
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void test_network_remote_push__cleanup(void)
{
	git_remote_free(_remote);
	_remote = NULL;

	git_repository_free(_repo);
	_repo = NULL;

	git_repository_free(_dummy);
	_dummy = NULL;

	cl_fixture_cleanup("testrepo.git");
	cl_fixture_cleanup("dummy.git");
}