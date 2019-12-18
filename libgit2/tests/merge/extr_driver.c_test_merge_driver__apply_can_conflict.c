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
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_get (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_merge_driver_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge_driver_unregister (char*) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  set_gitattributes_to (char*) ; 
 TYPE_1__ test_driver_conflict_apply ; 

void test_merge_driver__apply_can_conflict(void)
{
	const git_index_entry *ancestor, *ours, *theirs;

	cl_git_pass(git_merge_driver_register("conflict",
		&test_driver_conflict_apply.base));

    set_gitattributes_to("conflict");
    merge_branch();

	cl_git_pass(git_index_conflict_get(&ancestor, &ours, &theirs,
		repo_index, "automergeable.txt"));

	git_merge_driver_unregister("conflict");
}