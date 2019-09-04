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
struct TYPE_3__ {int /*<<< orphan*/  remote_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_origin_name_remote_create ; 
 TYPE_1__ g_options ; 
 int /*<<< orphan*/  g_remote ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void test_clone_nonetwork__custom_origin_name(void)
{
	g_options.remote_cb = custom_origin_name_remote_create;
	cl_git_pass(git_clone(&g_repo, cl_git_fixture_url("testrepo.git"), "./foo", &g_options));

	cl_git_pass(git_remote_lookup(&g_remote, g_repo, "my_origin"));
}