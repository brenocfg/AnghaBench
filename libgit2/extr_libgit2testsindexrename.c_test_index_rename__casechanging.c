#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {char* path; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_2__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_repo_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_index_rename__casechanging(void)
{
	git_repository *repo;
	git_index *index;
	const git_index_entry *entry;
	git_index_entry new = {{0}};

	p_mkdir("rename", 0700);

	cl_git_pass(git_repository_init(&repo, "./rename", 0));
	cl_git_pass(git_repository_index(&index, repo));

	cl_git_mkfile("./rename/lame.name.txt", "new_file\n");

	cl_git_pass(git_index_add_bypath(index, "lame.name.txt"));
	cl_assert_equal_i(1, git_index_entrycount(index));
	cl_assert((entry = git_index_get_bypath(index, "lame.name.txt", 0)));

	memcpy(&new, entry, sizeof(git_index_entry));
	new.path = "LAME.name.TXT";

	cl_git_pass(git_index_add(index, &new));
	cl_assert((entry = git_index_get_bypath(index, "LAME.name.TXT", 0)));

	if (cl_repo_get_bool(repo, "core.ignorecase"))
		cl_assert_equal_i(1, git_index_entrycount(index));
	else
		cl_assert_equal_i(2, git_index_entrycount(index));

	git_index_free(index);
	git_repository_free(repo);

	cl_fixture_cleanup("rename");
}