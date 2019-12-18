#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hack_index (char**) ; 
 int merge_branch () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  write_files (char**) ; 

__attribute__((used)) static int merge_differently_filtered_files(char *files[])
{
	git_reference *head;
	git_object *head_object;
	int error;

	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_peel(&head_object, head, GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(repo, head_object, GIT_RESET_HARD, NULL));

	/* Emulate checkout with a broken or misconfigured filter:  modify some
	 * files on-disk and then update the index with the updated file size
	 * and time, as if some filter applied them.  These files should not be
	 * treated as dirty since we created them.
	 *
	 * (Make sure to update the index stamp to defeat racy-git protections
	 * trying to sanity check the files in the index; those would rehash the
	 * files, showing them as dirty, the exact mechanism we're trying to avoid.)
	 */

	write_files(files);
	hack_index(files);

	cl_git_pass(git_index_write(repo_index));

	error = merge_branch();

	git_object_free(head_object);
	git_reference_free(head);

	return error;
}