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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  automergeable_id ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_repo_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  set_gitattributes_to (char*) ; 

void test_merge_driver__set_forces_text(void)
{
	const git_index_entry *idx;

	/* `merge` without specifying a driver indicates `text` */
	set_gitattributes_to("");
	cl_repo_set_string(repo, "merge.default", "custom");

	merge_branch();

	cl_assert((idx = git_index_get_bypath(repo_index, "automergeable.txt", 0)));
	cl_assert_equal_oid(&automergeable_id, &idx->id);
}