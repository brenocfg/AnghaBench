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
struct TYPE_5__ {char* path; void* mode; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EINDEXDIRTY ; 
 void* GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_OPT_ENABLE_UNSAVED_INDEX_SAFETY ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_from_buffer (int /*<<< orphan*/ *,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_is_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_index_tests__dirty_fails_optionally(void)
{
	git_repository *repo;
	git_index *index;
	git_index_entry entry = {{0}};

	/* Index is not dirty after opening */
	repo = cl_git_sandbox_init("testrepo");
	cl_git_pass(git_repository_index(&index, repo));

	/* Index is dirty after adding an entry */
	entry.mode = GIT_FILEMODE_BLOB;
	entry.path = "test.txt";
	cl_git_pass(git_index_add_from_buffer(index, &entry, "Hi.\n", 4));
	cl_assert(git_index_is_dirty(index));

	cl_git_pass(git_checkout_head(repo, NULL));

	/* Index is dirty (again) after adding an entry */
	entry.mode = GIT_FILEMODE_BLOB;
	entry.path = "test.txt";
	cl_git_pass(git_index_add_from_buffer(index, &entry, "Hi.\n", 4));
	cl_assert(git_index_is_dirty(index));

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_UNSAVED_INDEX_SAFETY, 1));
	cl_git_fail_with(GIT_EINDEXDIRTY, git_checkout_head(repo, NULL));

	git_index_free(index);
	cl_git_sandbox_cleanup();
}