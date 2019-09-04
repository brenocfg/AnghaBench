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
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_idx ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr_s (int /*<<< orphan*/ *) ; 

void test_index_bypath__add_submodule_unregistered(void)
{
	const char *sm_name = "not-submodule";
	const char *sm_head = "68e92c611b80ee1ed8f38314ff9577f0d15b2444";
	const git_index_entry *entry;

	cl_git_pass(git_index_add_bypath(g_idx, sm_name));

	cl_assert(entry = git_index_get_bypath(g_idx, sm_name, 0));
	cl_assert_equal_s(sm_head, git_oid_tostr_s(&entry->id));
	cl_assert_equal_s(sm_name, entry->path);
}