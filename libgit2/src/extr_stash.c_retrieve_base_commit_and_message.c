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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int append_commit_description (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int retrieve_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retrieve_base_commit_and_message(
	git_commit **b_commit,
	git_buf *stash_message,
	git_repository *repo)
{
	git_reference *head = NULL;
	int error;

	if ((error = retrieve_head(&head, repo)) < 0)
		return error;

	if (strcmp("HEAD", git_reference_name(head)) == 0)
		error = git_buf_puts(stash_message, "(no branch): ");
	else
		error = git_buf_printf(
			stash_message,
			"%s: ",
			git_reference_name(head) + strlen(GIT_REFS_HEADS_DIR));
	if (error < 0)
		goto cleanup;

	if ((error = git_commit_lookup(
			 b_commit, repo, git_reference_target(head))) < 0)
		goto cleanup;

	if ((error = append_commit_description(stash_message, *b_commit)) < 0)
		goto cleanup;

cleanup:
	git_reference_free(head);
	return error;
}