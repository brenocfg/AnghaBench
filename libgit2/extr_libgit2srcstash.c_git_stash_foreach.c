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
typedef  int (* git_stash_cb ) (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_REFS_STASH_FILE ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_reflog_entry_id_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 size_t git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_stash_foreach(
	git_repository *repo,
	git_stash_cb callback,
	void *payload)
{
	git_reference *stash;
	git_reflog *reflog = NULL;
	int error;
	size_t i, max;
	const git_reflog_entry *entry;

	error = git_reference_lookup(&stash, repo, GIT_REFS_STASH_FILE);
	if (error == GIT_ENOTFOUND) {
		git_error_clear();
		return 0;
	}
	if (error < 0)
		goto cleanup;

	if ((error = git_reflog_read(&reflog, repo, GIT_REFS_STASH_FILE)) < 0)
		goto cleanup;

	max = git_reflog_entrycount(reflog);
	for (i = 0; i < max; i++) {
		entry = git_reflog_entry_byindex(reflog, i);

		error = callback(i,
			git_reflog_entry_message(entry),
			git_reflog_entry_id_new(entry),
			payload);

		if (error) {
			git_error_set_after_callback(error);
			break;
		}
	}

cleanup:
	git_reference_free(stash);
	git_reflog_free(reflog);
	return error;
}