#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_11__ {TYPE_1__* worktree; TYPE_3__* repo; } ;
struct TYPE_10__ {int /*<<< orphan*/  workdir; } ;
struct TYPE_8__ {int /*<<< orphan*/  gitdir; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_6__ fixture ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_worktree_add (int /*<<< orphan*/ **,TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void test_worktree_worktree__init_existing_path(void)
{
	const char *wtfiles[] = { "HEAD", "commondir", "gitdir", "index" };
	git_worktree *wt;
	git_buf path = GIT_BUF_INIT;
	unsigned i;

	/* Delete files to verify they have not been created by
	 * the init call */
	for (i = 0; i < ARRAY_SIZE(wtfiles); i++) {
		cl_git_pass(git_buf_joinpath(&path,
			    fixture.worktree->gitdir, wtfiles[i]));
		cl_git_pass(p_unlink(path.ptr));
	}

	cl_git_pass(git_buf_joinpath(&path, fixture.repo->workdir, "../testrepo-worktree"));
	cl_git_fail(git_worktree_add(&wt, fixture.repo, "worktree-new", path.ptr, NULL));

	/* Verify files have not been re-created */
	for (i = 0; i < ARRAY_SIZE(wtfiles); i++) {
		cl_git_pass(git_buf_joinpath(&path,
			    fixture.worktree->gitdir, wtfiles[i]));
		cl_assert(!git_path_exists(path.ptr));
	}

	git_buf_dispose(&path);
}