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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/ * cfg ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/ * snapshot ; 

void test_config_snapshot__snapshot(void)
{
	git_config *snapshot_snapshot;
	int i;

	cl_git_mkfile("configfile", "[section]\nkey = 1\n");

	cl_git_pass(git_config_open_ondisk(&cfg, "configfile"));
	cl_git_pass(git_config_snapshot(&snapshot, cfg));

	cl_git_pass(git_config_snapshot(&snapshot_snapshot, snapshot));

	cl_git_pass(git_config_get_int32(&i, snapshot_snapshot, "section.key"));
	cl_assert_equal_i(i, 1);

	git_config_free(snapshot_snapshot);

	cl_git_pass(p_unlink("configfile"));
}