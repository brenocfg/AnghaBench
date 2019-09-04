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
 int /*<<< orphan*/ * _cl_repo ; 
 int /*<<< orphan*/ * _cl_sandbox ; 
 int /*<<< orphan*/  cl_fixture_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void cl_git_sandbox_cleanup(void)
{
	if (_cl_repo) {
		git_repository_free(_cl_repo);
		_cl_repo = NULL;
	}
	if (_cl_sandbox) {
		cl_fixture_cleanup(_cl_sandbox);
		_cl_sandbox = NULL;
	}
}