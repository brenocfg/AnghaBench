#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_off_t ;
struct TYPE_6__ {struct TYPE_6__* message; int /*<<< orphan*/  committer; int /*<<< orphan*/  author; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_note ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_BLOBSIZE (scalar_t__) ; 
 TYPE_1__* git__malloc (int) ; 
 TYPE_1__* git__strndup (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_author (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_signature_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int note_new(
	git_note **out,
	git_oid *note_oid,
	git_commit *commit,
	git_blob *blob)
{
	git_note *note = NULL;
	git_off_t blobsize;

	note = git__malloc(sizeof(git_note));
	GIT_ERROR_CHECK_ALLOC(note);

	git_oid_cpy(&note->id, note_oid);

	if (git_signature_dup(&note->author, git_commit_author(commit)) < 0 ||
		git_signature_dup(&note->committer, git_commit_committer(commit)) < 0)
		return -1;

	blobsize = git_blob_rawsize(blob);
	GIT_ERROR_CHECK_BLOBSIZE(blobsize);

	note->message = git__strndup(git_blob_rawcontent(blob), (size_t)blobsize);
	GIT_ERROR_CHECK_ALLOC(note->message);

	*out = note;
	return 0;
}