#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char** member_0; int member_1; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  find_master_haacked ; 
 int find_master_haacked_called ; 
 int found_haacked ; 
 int found_master ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_fetchhead_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_fetchhead_nonetwork__create_when_refpecs_given(void)
{
	git_remote *remote;
	git_buf path = GIT_BUF_INIT;
	char *refspec1 = "refs/heads/master";
	char *refspec2 = "refs/heads/haacked";
	char *refspecs[] = { refspec1, refspec2 };
	git_strarray specs = {
		refspecs,
		2,
	};

	cl_set_cleanup(&cleanup_repository, "./test1");
	cl_git_pass(git_repository_init(&g_repo, "./test1", 0));

	cl_git_pass(git_buf_joinpath(&path, git_repository_path(g_repo), "FETCH_HEAD"));
	cl_git_pass(git_remote_create(&remote, g_repo, "origin", cl_fixture("testrepo.git")));

	cl_assert(!git_path_exists(path.ptr));
	cl_git_pass(git_remote_fetch(remote, &specs, NULL, NULL));
	cl_assert(git_path_exists(path.ptr));

	cl_git_pass(git_repository_fetchhead_foreach(g_repo, find_master_haacked, NULL));
	cl_assert(find_master_haacked_called);
	cl_assert(found_master);
	cl_assert(found_haacked);

	git_remote_free(remote);
	git_buf_dispose(&path);
}