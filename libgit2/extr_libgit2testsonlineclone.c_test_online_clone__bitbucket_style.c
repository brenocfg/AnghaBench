#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* member_0; char* member_1; } ;
typedef  TYPE_3__ git_cred_userpass_payload ;
struct TYPE_6__ {TYPE_3__* payload; int /*<<< orphan*/  credentials; } ;
struct TYPE_7__ {TYPE_1__ callbacks; } ;
struct TYPE_9__ {TYPE_2__ fetch_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_REPO_URL ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_4__ g_options ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  git_cred_userpass ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void test_online_clone__bitbucket_style(void)
{
	git_cred_userpass_payload user_pass = {
		"libgit3", "libgit3"
	};

	g_options.fetch_opts.callbacks.credentials = git_cred_userpass;
	g_options.fetch_opts.callbacks.payload = &user_pass;

	cl_git_pass(git_clone(&g_repo, BB_REPO_URL, "./foo", &g_options));
	git_repository_free(g_repo); g_repo = NULL;
	cl_fixture_cleanup("./foo");
}