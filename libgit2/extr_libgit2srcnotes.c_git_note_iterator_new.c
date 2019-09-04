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
typedef  int /*<<< orphan*/  git_note_iterator ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_note_commit_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int retrieve_note_commit (int /*<<< orphan*/ **,char**,int /*<<< orphan*/ *,char const*) ; 

int git_note_iterator_new(
	git_note_iterator **it,
	git_repository *repo,
	const char *notes_ref_in)
{
	int error;
	git_commit *commit = NULL;
	char *notes_ref;

	error = retrieve_note_commit(&commit, &notes_ref, repo, notes_ref_in);
	if (error < 0)
		goto cleanup;

	error = git_note_commit_iterator_new(it, commit);

cleanup:
	git__free(notes_ref);
	git_commit_free(commit);

	return error;
}