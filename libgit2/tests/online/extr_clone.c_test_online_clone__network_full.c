#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  download_tags; } ;
typedef  TYPE_1__ git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_AUTO ; 
 int /*<<< orphan*/  LIVE_REPO_URL ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_lookup (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 

void test_online_clone__network_full(void)
{
	git_remote *origin;

	cl_git_pass(git_clone(&g_repo, LIVE_REPO_URL, "./foo", &g_options));
	cl_assert(!git_repository_is_bare(g_repo));
	cl_git_pass(git_remote_lookup(&origin, g_repo, "origin"));

	cl_assert_equal_i(GIT_REMOTE_DOWNLOAD_TAGS_AUTO, origin->download_tags);

	git_remote_free(origin);
}