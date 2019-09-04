#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  automergeable_id ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_driver_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge_driver_unregister (char*) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 TYPE_2__ test_driver_defer_apply ; 

void test_merge_driver__mergedefault_deferring_falls_back_to_text(void)
{
	const git_index_entry *idx;

	cl_git_pass(git_merge_driver_register("defer",
		&test_driver_defer_apply.base));

	cl_repo_set_string(repo, "merge.default", "defer");
	merge_branch();

	cl_assert((idx = git_index_get_bypath(repo_index, "automergeable.txt", 0)));
	cl_assert_equal_oid(&automergeable_id, &idx->id);

	git_merge_driver_unregister("defer");
}