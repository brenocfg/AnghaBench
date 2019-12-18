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
 int /*<<< orphan*/  backend ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_backend_delete (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_backend_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_backend_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_config_backend_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_backend (char*) ; 

void test_config_memory__write_operations_fail(void)
{
	setup_backend("");
	cl_git_fail(git_config_backend_set_string(backend, "general.foo", "var"));
	cl_git_fail(git_config_backend_delete(backend, "general.foo"));
	cl_git_fail(git_config_backend_lock(backend));
	cl_git_fail(git_config_backend_unlock(backend, 0));
}