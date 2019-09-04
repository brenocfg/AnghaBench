#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_3__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_note_author (int /*<<< orphan*/ *) ; 
 int git_note_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_message (int /*<<< orphan*/ *) ; 
 int git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int git_signature_default (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 

__attribute__((used)) static int rebase_copy_note(
	git_rebase *rebase,
	const char *notes_ref,
	git_oid *from,
	git_oid *to,
	const git_signature *committer)
{
	git_note *note = NULL;
	git_oid note_id;
	git_signature *who = NULL;
	int error;

	if ((error = git_note_read(&note, rebase->repo, notes_ref, from)) < 0) {
		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			error = 0;
		}

		goto done;
	}

	if (!committer) {
		if((error = git_signature_default(&who, rebase->repo)) < 0) {
			if (error != GIT_ENOTFOUND ||
				(error = git_signature_now(&who, "unknown", "unknown")) < 0)
				goto done;

			git_error_clear();
		}

		committer = who;
	}

	error = git_note_create(&note_id, rebase->repo, notes_ref,
		git_note_author(note), committer, to, git_note_message(note), 0);

done:
	git_note_free(note);
	git_signature_free(who);

	return error;
}