#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct prefix_count {char* member_0; int member_2; int /*<<< orphan*/  count; int /*<<< orphan*/  expected; scalar_t__ prefix; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  count_refs ; 
 int count_refs_called ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_add_fetch (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_fetchhead_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct prefix_count**) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_fetchhead_nonetwork__create_with_multiple_refspecs(void)
{
	git_remote *remote;
	git_buf path = GIT_BUF_INIT;

	cl_set_cleanup(&cleanup_repository, "./test1");
	cl_git_pass(git_repository_init(&g_repo, "./test1", 0));

	cl_git_pass(git_remote_create(&remote, g_repo, "origin", cl_fixture("testrepo.git")));
	git_remote_free(remote);
	cl_git_pass(git_remote_add_fetch(g_repo, "origin", "+refs/notes/*:refs/origin/notes/*"));
	/* Pick up the new refspec */
	cl_git_pass(git_remote_lookup(&remote, g_repo, "origin"));

	cl_git_pass(git_buf_joinpath(&path, git_repository_path(g_repo), "FETCH_HEAD"));
	cl_assert(!git_path_exists(path.ptr));
	cl_git_pass(git_remote_fetch(remote, NULL, NULL, NULL));
	cl_assert(git_path_exists(path.ptr));

	{
		int i;
		struct prefix_count prefix_counts[] = {
			{"refs/notes/", 0, 1},
			{"refs/heads/", 0, 12},
			{"refs/tags/", 0, 7},
			{NULL, 0, 0},
		};

		cl_git_pass(git_repository_fetchhead_foreach(g_repo, count_refs, &prefix_counts));
		cl_assert(count_refs_called);
		for (i = 0; prefix_counts[i].prefix; i++)
			cl_assert_equal_i(prefix_counts[i].expected, prefix_counts[i].count);
	}

	git_remote_free(remote);
	git_buf_dispose(&path);
}