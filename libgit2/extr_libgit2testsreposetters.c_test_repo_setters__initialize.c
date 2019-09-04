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
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  repo ; 

void test_repo_setters__initialize(void)
{
	cl_fixture_sandbox("testrepo.git");
	cl_git_pass(git_repository_open(&repo, "testrepo.git"));
	cl_must_pass(p_mkdir("new_workdir", 0777));
}