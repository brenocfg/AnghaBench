#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {char* path; void* mode; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 void* GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_2__ const*) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_add_from_buffer (int /*<<< orphan*/ *,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_uptodate_files(void)
{
	git_buf path = GIT_BUF_INIT;
	git_index *index;
	const git_index_entry *a_entry;
	git_index_entry new_entry = {{0}};

	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_pass(git_buf_joinpath(&path, git_repository_workdir(g_repo), "A"));
	cl_git_mkfile(path.ptr, "A");

	/* Put 'A' into the index */
	cl_git_pass(git_index_add_bypath(index, "A"));

	cl_assert((a_entry = git_index_get_bypath(index, "A", 0)));

	/* Put 'B' into the index */
	new_entry.path = "B";
	new_entry.mode = GIT_FILEMODE_BLOB;
	git_oid_cpy(&new_entry.id, &a_entry->id);
	cl_git_pass(git_index_add(index, &new_entry));

	/* Put 'C' into the index */
	new_entry.path = "C";
	new_entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_index_add_from_buffer(index, &new_entry, "hello!\n", 7));

	git_index_free(index);
	git_buf_dispose(&path);
}