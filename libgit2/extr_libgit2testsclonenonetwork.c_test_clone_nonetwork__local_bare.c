#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bare; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 

void test_clone_nonetwork__local_bare(void)
{
	g_options.bare = true;
	cl_git_pass(git_clone(&g_repo, cl_git_fixture_url("testrepo.git"), "./foo", &g_options));
}