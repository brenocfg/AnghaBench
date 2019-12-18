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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_SORT_REVERSE ; 
 int GIT_SORT_TIME ; 
 int GIT_SORT_TOPOLOGICAL ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_head ; 
 int /*<<< orphan*/  commit_sorting_time ; 
 int /*<<< orphan*/  commit_sorting_time_reverse ; 
 int /*<<< orphan*/  commit_sorting_topo ; 
 int /*<<< orphan*/  commit_sorting_topo_reverse ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

void test_revwalk_basic__sorting_modes(void)
{
	git_oid id;

	revwalk_basic_setup_walk(NULL);

	git_oid_fromstr(&id, commit_head);

	cl_git_pass(test_walk(_walk, &id, GIT_SORT_TIME, commit_sorting_time, 1));
	cl_git_pass(test_walk(_walk, &id, GIT_SORT_TOPOLOGICAL, commit_sorting_topo, 2));
	cl_git_pass(test_walk(_walk, &id, GIT_SORT_TIME | GIT_SORT_REVERSE, commit_sorting_time_reverse, 1));
	cl_git_pass(test_walk(_walk, &id, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE, commit_sorting_topo_reverse, 2));
}