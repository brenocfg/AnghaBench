#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * theirs; int /*<<< orphan*/ * ours; int /*<<< orphan*/ * ancestor; } ;
typedef  TYPE_1__ git_index_name_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_name_add (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int git_index_name_entrycount (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_index_name_get_byindex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_index ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

void test_index_names__roundtrip(void)
{
	const git_index_name_entry *conflict_name;

	cl_git_pass(git_index_name_add(repo_index, "ancestor", "ours", "theirs"));
	cl_git_pass(git_index_name_add(repo_index, "ancestor2", "ours2", NULL));
	cl_git_pass(git_index_name_add(repo_index, "ancestor3", NULL, "theirs3"));

	cl_git_pass(git_index_write(repo_index));
	git_index_clear(repo_index);
	cl_assert(git_index_name_entrycount(repo_index) == 0);

	cl_git_pass(git_index_read(repo_index, true));
	cl_assert(git_index_name_entrycount(repo_index) == 3);

	conflict_name = git_index_name_get_byindex(repo_index, 0);
	cl_assert(strcmp(conflict_name->ancestor, "ancestor") == 0);
	cl_assert(strcmp(conflict_name->ours, "ours") == 0);
	cl_assert(strcmp(conflict_name->theirs, "theirs") == 0);

	conflict_name = git_index_name_get_byindex(repo_index, 1);
	cl_assert(strcmp(conflict_name->ancestor, "ancestor2") == 0);
	cl_assert(strcmp(conflict_name->ours, "ours2") == 0);
	cl_assert(conflict_name->theirs == NULL);

	conflict_name = git_index_name_get_byindex(repo_index, 2);
	cl_assert(strcmp(conflict_name->ancestor, "ancestor3") == 0);
	cl_assert(conflict_name->ours == NULL);
	cl_assert(strcmp(conflict_name->theirs, "theirs3") == 0);
}