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
typedef  int /*<<< orphan*/  git_config_backend ;

/* Variables and functions */
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_add_backend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_backend_from_string (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snapshot ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_config_snapshot__snapshot_from_in_memony(void)
{
	const char *configuration = "[section]\nkey = 1\n";
	git_config_backend *backend;
	int i;

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_backend_from_string(&backend, configuration, strlen(configuration)));
	cl_git_pass(git_config_add_backend(cfg, backend, 0, NULL, 0));

	cl_git_pass(git_config_snapshot(&snapshot, cfg));
	cl_git_pass(git_config_get_int32(&i, snapshot, "section.key"));
	cl_assert_equal_i(i, 1);
}