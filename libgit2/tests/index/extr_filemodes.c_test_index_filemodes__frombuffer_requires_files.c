#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  new_entry ;
struct TYPE_7__ {char* path; void* mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 void* GIT_FILEMODE_BLOB ; 
 void* GIT_FILEMODE_BLOB_EXECUTABLE ; 
 void* GIT_FILEMODE_COMMIT ; 
 void* GIT_FILEMODE_LINK ; 
 void* GIT_FILEMODE_TREE ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (void*,void*) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_from_buffer (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_index_filemodes__frombuffer_requires_files(void)
{
	git_index *index;
	git_index_entry new_entry;
	const git_index_entry *ret_entry;
	const char *content = "hey there\n";

	memset(&new_entry, 0, sizeof(new_entry));
	cl_git_pass(git_repository_index(&index, g_repo));

	/* regular blob */
	new_entry.path = "dummy-file.txt";
	new_entry.mode = GIT_FILEMODE_BLOB;

	cl_git_pass(git_index_add_from_buffer(index,
		&new_entry, content, strlen(content)));

	cl_assert((ret_entry = git_index_get_bypath(index, "dummy-file.txt", 0)));
	cl_assert_equal_s("dummy-file.txt", ret_entry->path);
	cl_assert_equal_i(GIT_FILEMODE_BLOB, ret_entry->mode);

	/* executable blob */
	new_entry.path = "dummy-file.txt";
	new_entry.mode = GIT_FILEMODE_BLOB_EXECUTABLE;

	cl_git_pass(git_index_add_from_buffer(index,
		&new_entry, content, strlen(content)));

	cl_assert((ret_entry = git_index_get_bypath(index, "dummy-file.txt", 0)));
	cl_assert_equal_s("dummy-file.txt", ret_entry->path);
	cl_assert_equal_i(GIT_FILEMODE_BLOB_EXECUTABLE, ret_entry->mode);

	/* links are also acceptable */
	new_entry.path = "dummy-link.txt";
	new_entry.mode = GIT_FILEMODE_LINK;

	cl_git_pass(git_index_add_from_buffer(index,
		&new_entry, content, strlen(content)));

	cl_assert((ret_entry = git_index_get_bypath(index, "dummy-link.txt", 0)));
	cl_assert_equal_s("dummy-link.txt", ret_entry->path);
	cl_assert_equal_i(GIT_FILEMODE_LINK, ret_entry->mode);

	/* trees are rejected */
	new_entry.path = "invalid_mode.txt";
	new_entry.mode = GIT_FILEMODE_TREE;

	cl_git_fail(git_index_add_from_buffer(index,
		&new_entry, content, strlen(content)));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, "invalid_mode.txt", 0));

	/* submodules are rejected */
	new_entry.path = "invalid_mode.txt";
	new_entry.mode = GIT_FILEMODE_COMMIT;

	cl_git_fail(git_index_add_from_buffer(index,
		&new_entry, content, strlen(content)));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, "invalid_mode.txt", 0));

	git_index_free(index);
}