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
 int /*<<< orphan*/  cl_fixture_cleanup (void*) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 

__attribute__((used)) static void cleanup_fixture_submodules(void *payload)
{
	cl_git_sandbox_cleanup(); /* either "submodules" or "submod2" */

	if (payload)
		cl_fixture_cleanup(payload);
}