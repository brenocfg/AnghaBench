#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_repository_fetchhead_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_noop ; 

void test_fetchhead_nonetwork__invalid_description(void)
{
	cl_set_cleanup(&cleanup_repository, "./test1");
	cl_git_pass(git_repository_init(&g_repo, "./test1", 0));

	cl_git_rewritefile("./test1/.git/FETCH_HEAD", "49322bb17d3acc9146f98c97d078513228bbf3c0\tnot-for-merge\n");
	cl_git_fail(git_repository_fetchhead_foreach(g_repo, read_noop, NULL));

	cl_assert(git__prefixcmp(git_error_last()->message, "invalid description") == 0);
}