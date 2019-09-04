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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note_iterator ;
typedef  int (* git_note_foreach_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 int /*<<< orphan*/  git_note_iterator_free (int /*<<< orphan*/ *) ; 
 int git_note_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int git_note_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_note_foreach(
	git_repository *repo,
	const char *notes_ref,
	git_note_foreach_cb note_cb,
	void *payload)
{
	int error;
	git_note_iterator *iter = NULL;
	git_oid note_id, annotated_id;

	if ((error = git_note_iterator_new(&iter, repo, notes_ref)) < 0)
		return error;

	while (!(error = git_note_next(&note_id, &annotated_id, iter))) {
		if ((error = note_cb(&note_id, &annotated_id, payload)) != 0) {
			git_error_set_after_callback(error);
			break;
		}
	}

	if (error == GIT_ITEROVER)
		error = 0;

	git_note_iterator_free(iter);
	return error;
}