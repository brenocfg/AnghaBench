#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_9__ {int /*<<< orphan*/  on_disk; int /*<<< orphan*/  index_file_path; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_myrepo ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_index_entrycount (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_index_write (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void test_index_tests__reload_from_disk(void)
{
	git_repository *repo;
	git_index *read_index;
	git_index *write_index;

	cl_set_cleanup(&cleanup_myrepo, NULL);

	cl_git_pass(git_futils_mkdir("./myrepo", 0777, GIT_MKDIR_PATH));
	cl_git_mkfile("./myrepo/a.txt", "a\n");
	cl_git_mkfile("./myrepo/b.txt", "b\n");

	cl_git_pass(git_repository_init(&repo, "./myrepo", 0));
	cl_git_pass(git_repository_index(&write_index, repo));
	cl_assert_equal_i(false, write_index->on_disk);

	cl_git_pass(git_index_open(&read_index, write_index->index_file_path));
	cl_assert_equal_i(false, read_index->on_disk);

	/* Stage two new files against the write_index */
	cl_git_pass(git_index_add_bypath(write_index, "a.txt"));
	cl_git_pass(git_index_add_bypath(write_index, "b.txt"));

	cl_assert_equal_sz(2, git_index_entrycount(write_index));

	/* Persist the index changes to disk */
	cl_git_pass(git_index_write(write_index));
	cl_assert_equal_i(true, write_index->on_disk);

	/* Sync the changes back into the read_index */
	cl_assert_equal_sz(0, git_index_entrycount(read_index));

	cl_git_pass(git_index_read(read_index, true));
	cl_assert_equal_i(true, read_index->on_disk);

	cl_assert_equal_sz(2, git_index_entrycount(read_index));

	/* Remove the index file from the filesystem */
	cl_git_pass(p_unlink(write_index->index_file_path));

	/* Sync the changes back into the read_index */
	cl_git_pass(git_index_read(read_index, true));
	cl_assert_equal_i(false, read_index->on_disk);
	cl_assert_equal_sz(0, git_index_entrycount(read_index));

	git_index_free(read_index);
	git_index_free(write_index);
	git_repository_free(repo);
}