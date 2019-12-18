#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {char* path; int /*<<< orphan*/  mode; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_from_buffer (int /*<<< orphan*/ *,TYPE_2__*,char*,int) ; 
 int git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_is_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 

void test_index_tests__dirty_and_clean(void)
{
	git_repository *repo;
	git_index *index;
	git_index_entry entry = {{0}};

	/* Index is not dirty after opening */
	cl_git_pass(git_repository_init(&repo, "./myrepo", 0));
	cl_git_pass(git_repository_index(&index, repo));

	cl_assert(git_index_entrycount(index) == 0);
	cl_assert(!git_index_is_dirty(index));

	/* Index is dirty after adding an entry */
	entry.mode = GIT_FILEMODE_BLOB;
	entry.path = "test.txt";
	cl_git_pass(git_index_add_from_buffer(index, &entry, "Hi.\n", 4));
	cl_assert(git_index_entrycount(index) == 1);
	cl_assert(git_index_is_dirty(index));

	/* Index is not dirty after write */
	cl_git_pass(git_index_write(index));
	cl_assert(!git_index_is_dirty(index));

	/* Index is dirty after removing an entry */
	cl_git_pass(git_index_remove_bypath(index, "test.txt"));
	cl_assert(git_index_entrycount(index) == 0);
	cl_assert(git_index_is_dirty(index));

	/* Index is not dirty after write */
	cl_git_pass(git_index_write(index));
	cl_assert(!git_index_is_dirty(index));

	/* Index remains not dirty after read */
	cl_git_pass(git_index_read(index, 0));
	cl_assert(!git_index_is_dirty(index));

	/* Index is dirty when we do an unforced read with dirty content */
	cl_git_pass(git_index_add_from_buffer(index, &entry, "Hi.\n", 4));
	cl_assert(git_index_entrycount(index) == 1);
	cl_assert(git_index_is_dirty(index));

	cl_git_pass(git_index_read(index, 0));
	cl_assert(git_index_is_dirty(index));

	/* Index is clean when we force a read with dirty content */
	cl_git_pass(git_index_read(index, 1));
	cl_assert(!git_index_is_dirty(index));

	git_index_free(index);
	git_repository_free(repo);
}