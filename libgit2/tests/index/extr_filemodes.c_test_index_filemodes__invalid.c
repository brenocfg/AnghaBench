#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_index_filemodes__invalid(void)
{
	git_index *index;
	git_index_entry entry;
	const git_index_entry *dummy;

	cl_git_pass(git_repository_index(&index, g_repo));

	/* add a dummy file so that we have a valid id */
	cl_git_mkfile("./filemodes/dummy-file.txt", "new-file\n");
	cl_git_pass(git_index_add_bypath(index, "dummy-file.txt"));
	cl_assert((dummy = git_index_get_bypath(index, "dummy-file.txt", 0)));

	GIT_INDEX_ENTRY_STAGE_SET(&entry, 0);
	entry.path = "foo";
	entry.mode = GIT_OBJECT_BLOB;
	git_oid_cpy(&entry.id, &dummy->id);
	cl_git_fail(git_index_add(index, &entry));

	entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_index_add(index, &entry));

	git_index_free(index);
}