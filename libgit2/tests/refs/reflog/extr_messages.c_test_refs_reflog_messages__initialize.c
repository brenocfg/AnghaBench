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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_email ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_set_ident (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void test_refs_reflog_messages__initialize(void)
{
	g_repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_set_ident(g_repo, "Foo Bar", g_email));
}